/*
Простой TCP-клиент.
Получает текстовую строку, преобразует ее в верхний регистр и возвращает клиенту результат.
*/

#define _CRT_SECURE_NO_WARNINGS 
#include "stdafx.h" 
#include <conio.h> 
#include <Winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#define SERVICE_PORT 1500
using namespace std;


int send_string(SOCKET s, const char * sString);

int main()
{
	SOCKET S;	//декспритор сокета для соединения
	sockaddr_in serv_addr;
	WSADATA wsadata;
	char sName[128];
	bool bTerminate = false;
	// Инициализация библиотеки сокетов
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	// Получение имени текущей машины
	gethostname(sName, sizeof(sName));
	printf("\nClient host: %s\n", sName);
	// Создание сокета
	// Для TCP-сокета - SOCK_STREAM
	// Для UDP - SOCK_DGRAM
	if ((S = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		fprintf(stderr, "Can't create socket\n");
		exit(1);
	}
	// Заполняем структуру адресов
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	// Разрешаем работу на всех доступных сетевых интерфейсах, в частности localhost
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// преобразование порядка байт
	serv_addr.sin_port = htons((u_short)SERVICE_PORT);
	// Подключение
	if (connect(S, (sockaddr*)&serv_addr, sizeof(serv_addr)) == INVALID_SOCKET)
	{
		fprintf(stderr, "Can't connect\n");
		_getch();
		exit(1);
	}
	// Основной цикл обработки подключения

	while (!bTerminate)
	{

		char sReceiveBuffer[1024] = { 0 };
		// Получаем и обрабатываем данные от сервера
		int nReaded = recv(S, sReceiveBuffer, sizeof(sReceiveBuffer) - 1, 0);
		// В случае ошибки (например, отсоединения сервера) выходим
		if (nReaded <= 0) break;
		// Мы получаем поток байт, поэтому нужно самостоятельно 
		// добавить завершающий 0 для ASCII строки 
		sReceiveBuffer[nReaded] = '\0';
		// Отбрасываем символы перевода строк
		for (char* pPtr = sReceiveBuffer; *pPtr != 0; pPtr++)
		{
			if (*pPtr == '\n' || *pPtr == '\r')
			{
				*pPtr = 0;
				break;
			}
		}
		// Пропускаем пустые строки
		if (sReceiveBuffer[0] == 0) continue;
		printf("%s\n", sReceiveBuffer);
		char sSendBuffer[1024];
		std::cin >> sSendBuffer;
		send_string(S, sSendBuffer);
	}
	// Закрываем клиентский сокет
	closesocket(S);
	// освобождаем ресурсы библиотеки сокетов
	WSACleanup();
	return 0;
}

// Функция отсылки текстовой ascii строки серверу
int send_string(SOCKET s, const char * sString)
{
	return send(s, sString, strlen(sString), 0);
}



