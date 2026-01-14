//#include "Include.h"
//
//Mysql sql;
//
//
//Mysql::Mysql()
//{
//}
//
//Mysql::~Mysql()
//{
//	mysql_close(connection);
//}
//
//void Mysql::Init()
//{
//}
//
//void Mysql::Update(double frame)
//{
//}
//
//void Mysql::Draw()
//{
//}
//
//void Mysql::save()
//{
//	sprintf_s(name, "%s", "wsj");
//	sprintf_s(address, "%s", "777");
//	sprintf_s(query, "insert into login values "
//		"('%s', '%s')", name, address);
//	query_start = mysql_query(connection, query);
//	if (query_start != 0) // 전송 실패시
//	{
//		sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
//		sql.mysql_Success = false;
//	}
//	else // 성공시
//	{
//		mysql_Success = true;
//	}
//}
