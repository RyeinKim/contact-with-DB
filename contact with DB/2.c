#define _CRT_SECURE_NO_WARNINGS
#include <mysql.h>
#include <string.h>
#include <stdio.h>

#define DB_HOST "reignking.cafe24.com"
#define DB_USER "reignking"
#define DB_PASS "djaak4250"
#define DB_NAME "reignking"
#define CHOP(x) x[strlen(x) - 1] = ' '

MYSQL *connection = NULL, conn;
MYSQL_RES   *sql_result;
MYSQL_ROW   sql_row;

typedef struct {
	char name[10];
	char digit[20];
	char address[256];
} _contact;

int query_stat;
char query[255];

void mysql_start();
void input_data(_contact *contact);
void print(MYSQL *connection);
void search(MYSQL *connection);

int main(void)
{
	while (1)
	{
		int m;
		_contact m1;
		mysql_start();

		printf("type:");
		scanf("%d", &m);
		getchar();

		if (m == 4) { break; }
		switch (m)
		{
			case 1:
			{
				input_data(&m1);
				break;
			}
			case 2:
			{
				print(connection);
				break;
			}
			case 3:
			{
				search(connection);
				break;
			}
			default:
			{
				break;
			}
		}
		mysql_close(connection);
	}
}

void mysql_start()
{
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST,
		DB_USER, DB_PASS,
		DB_NAME, 3306,
		(char *)NULL, 0);

	if (connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return 1;
	}

	query_stat = mysql_query(connection, "select * from test");
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	sql_result = mysql_store_result(connection);
	mysql_free_result(sql_result);
}

void input_data(_contact *contact)
{
	printf("이름 :");
	fgets(contact->name, 20, stdin);
	CHOP(contact->name);

	printf("전화 :");
	fgets(contact->digit, 20, stdin);
	CHOP(contact->digit);

	printf("주소 :");
	fgets(contact->address, 256, stdin);
	CHOP(contact->address);

	sprintf(query, "insert into test values "
		"('%s', '%s', '%s')",
		contact->name, contact->digit, contact->address);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}
}

void print(MYSQL *connection)
{
	int field;
	mysql_query(connection, "select * from test");
	sql_result = mysql_store_result(connection);
	field = mysql_num_fields(sql_result);
	while ((sql_row = mysql_fetch_row(sql_result)))
	{
		for (int i = 0; i < field; i++)
		{
			printf("%s\n", sql_row[i]);
		}
		printf("\n");
	}
}

void search(MYSQL *connection)
{
	char name[20];
	int field;
	printf("insert name : ");
	scanf("%s", name);
	sprintf(query, "select * from test where name = '%s'", name);
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	field = mysql_num_fields(sql_result);
	while ((sql_row = mysql_fetch_row(sql_result)))
	{
		for (int i = 0; i < field; i++)
			printf("%s\n", sql_row[i]);
		printf("\n");
	}
}