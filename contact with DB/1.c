#include <mysql.h>
#include <string.h>
#include <stdio.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "sungjuk"
#define CHOP(x) x[strlen(x) - 1] = ' '
typedef struct {
	char name[10];
	int jumsu[3];
	float ave;
	int total;
} _sungjuk;
void input_data(_sungjuk *sungjuk);
int insert(MYSQL *, _sungjuk sungjuk);
int search(MYSQL *);
int print(MYSQL *);
int main(void)
{
	int i, n;
	MYSQL *connection = NULL, conn;
	MYSQL_RES *sql_result;
	MYSQL_ROW row;
	int field;
	int query_stat;
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);
	if (connection == NULL) {
		printf("connect error!\n");
		exit(1);
	}
	_sungjuk sungjuk[5];
	printf("Enter the mode:\n");
	printf("1 : input mode\n");
	printf("2 : seaching mode\n");
	printf("3 : print all\n");
	scanf("%d", &n);
	switch (n)
	{
	case 1:
		for (i = 0; i < 2; i++)
			input_data(&sungjuk[i]);

		for (i = 0; i < 2; i++) {
			printf("%p\n", connection);
			insert(connection, sungjuk[i]);
		}
		break;
	case 2:
		search(connection);
		break;
	case 3:
		print(connection);
		break;
	default:
		exit(1);
	}
	mysql_close(connection);
}

void input_data(_sungjuk *sungjuk)
{
	printf("input name\n");
	scanf("%s", sungjuk->name);
	getchar();
	printf("input KOREAN score\n");
	scanf("%d", &sungjuk->jumsu[0]);
	printf("input ENGLISH score\n");
	scanf("%d", &sungjuk->jumsu[1]);
	printf("input MATH score\n");
	scanf("%d", &sungjuk->jumsu[2]);
	sungjuk->total = sungjuk->jumsu[0] + sungjuk->jumsu[1] + sungjuk->jumsu[2];
	sungjuk->ave = (float)sungjuk->total / 3.0;
}

int insert(MYSQL *con, _sungjuk sungjuk)
{
	char buff[255];
	sprintf(buff, "insert into test values ('%s', '%s', '%s')", sungjuk.name, sungjuk.jumsu[0], sungjuk.jumsu[1], sungjuk.jumsu[2], sungjuk.total, sungjuk.ave);

	printf("%s : %p: %d\n", buff, con, mysql_query(con, buff));
}

int search(MYSQL *con)
{
	int j;
	char buff2[255];
	char name[20];

	MYSQL_RES *sql_result;
	MYSQL_ROW row;
	int field;
	printf("insert name : ");
	scanf("%s", name);
	sprintf(buff2, "select * from test where name = '%s'", name);
	mysql_query(con, buff2);
	sql_result = mysql_store_result(con);
	field = mysql_num_fields(sql_result);
	printf("%12s%12s%12s%12s%12s%12s", "name", "KREAN", "ENGLISH", "MATH", "SUM", "AVER");
	while ((row = mysql_fetch_row(sql_result))) {
		for (j = 0; j < field; j++)
			printf("%12s", row[j]);
		printf("\n");
	}
}

int print(MYSQL *con)
{
	int k;
	MYSQL_RES *sql_result;
	MYSQL_ROW row;
	int field;
	mysql_query(con, "select * from test");
	sql_result = mysql_store_result(con);
	field = mysql_num_fields(sql_result);
	printf("%12s%12s%12s%12s%12s%12s", "name", "KREAN", "ENGLISH", "MATH", "SUM", "AVER");
	while ((row = mysql_fetch_row(sql_result))) {
		for (k = 0; k < field; k++)
			printf("%12s", row[k]);
		printf("\n");
	}
}