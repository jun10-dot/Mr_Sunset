//#pragma once
//#include "Include.h"
//
//class Mysql
//{
//
//public:
//	Mysql();
//	~Mysql();
//
//	MYSQL mysql;
//
//	// MYSQL 연결 및 구동 변수
//	MYSQL		*connection = NULL, conn;
//	MYSQL_RES	*sql_result;
//	MYSQL_ROW	sql_row;
//	int query_start;
//
//	// 데이타 베이스 칼럼 저장 변수
//	char name[12];
//	char address[80];
//	char tel[12];
//	char query[255];
//
//	// MYSQL 상태 변수
//	char state[256];
//	bool mysql_Success;
//
//	// MYSQL 결과 확인 변수
//	char result[256];
//
//	void Init();
//	void Update(double frame);
//	void Draw();
//	void save();
//};
//
//extern Mysql sql;