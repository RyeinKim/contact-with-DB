#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <mysql.h>

#define DB_HOST "183.111.182.200"
#define DB_USER "reignking"
#define DB_PASS "djaak4250"
#define DB_NAME "reignking"
#define CHOP(x) x[strlen(x) - 1] = ' '

MYSQL *con;
MYSQL_RES *res;
MYSQL_ROW row;



void input_data(_contact *contact);
int insert(MYSQL *con, _contact *contact);
int print(MYSQL *con);

void main() {
	con = mysql_init(NULL);
	mysql_init(con);
	if (mysql_real_connect(con, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0))
	{
		printf("success\n");
		mysql_set_character_set(con, "euckr");
		mysql_query(con, "set names euckr");
	}
	else printf("error");

	while (1)
	{
		int menu;
		_contact m1;

		printf("type : ");
		scanf("%d	", &menu);

		switch (menu)
		{
			case 1:
			{
					input_data(&m1);
				insert(con, &m1);
				break;
			}
			case 2:
			{
				print(con);
				break;
			}
		}
		mysql_query(con, "set names euckr");
		mysql_close(con);
	}
}

void input_data(_contact *contact)
{
	printf("input name\n");
	scanf("%s", contact->name);
	printf("input  digit\n");
	scanf("%s", contact->digit);
	printf("input address\n");
	scanf("%s", contact->address);
}

int insert(MYSQL *con, _contact *contact)
{
	char query[1024];
	sprintf(query, "insert into test values ('%s', '%s', '%s')", contact->name, contact->digit, contact->address);
	mysql_query(con, query);
	res = mysql_store_result(con);
}

int print(MYSQL *con)
{
	int k;
	int field;
	mysql_query(con, "select * from test");
	res = mysql_store_result(con);
	field = mysql_num_fields(res);
	printf("%s %s %s ", "name", "digit", "address");
	while ((row = mysql_fetch_row(res))) {
		for (k = 0; k < field; k++)
			printf("%s\n", row[k]);
		printf("\n");
	}
}