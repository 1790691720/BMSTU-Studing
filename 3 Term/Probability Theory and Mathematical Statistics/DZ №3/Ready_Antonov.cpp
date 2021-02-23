
#include <stdio.h>
#include <cmath>
#include <iostream>
using std::abs;

double factorial(int n)
{
	return (n < 2) ? 1 : n * factorial(n - 1);
}

int task_1(double waiting_time, double service_time)
{
	int operators = 1; // кол-во операторов
	long double p_refuse = 1; // вер-ть отказа
	double M_op = 0; // мат. ожидание занятых операторов
	double cof; // коэф-нт загрузки операторов
	double P_0 = 0;
	double sum = 0;
	int i;
	double P_work;
	do {
		for (i = 0; i <= operators; i++) {
			sum = sum + (pow(waiting_time / service_time, i) / factorial(i));
		}
		P_0 = 1 / sum;
		p_refuse = P_0 * powl(waiting_time, operators) / (powl(service_time, operators) * factorial(operators));
		if (p_refuse > 0.01) {
			printf("\nЧисло операторов- %d.\n", operators);
			printf("Вероятность отказа- %Lf.\n", p_refuse);
			P_work = 1 - p_refuse;
			for (i = 1; i <= operators; i++) {
				M_op = M_op + i * P_0 * powl(waiting_time, i) / (powl(service_time, i) * factorial(i));
			}
			printf("Мат ожидание занятых операторов- %lf.\n", M_op);
			cof = P_work * waiting_time / (operators * service_time);
			printf("Коэффицент занятости- %lf.\n", cof);
		}
		sum = 0;
		M_op = 0;
		operators++;
	} while (p_refuse > 0.01);
	printf("Далее вероятность отказа будет меньше 0.01.\n\n");
	return(operators - 2);
}

void task_2(int max_op, double waiting_time, double service_time)
{
	double P_0, P_refuse;
	double A = waiting_time / service_time;
	double sum = 0;
	double M_op = 0;
	double cof;
	double P_qu;
	double M_qu = 0;
	double cof_qu;
	int i;
	int operators, queue_lenght;
	printf("От мест в очереди.\n");
	for (operators = 1; operators <= max_op; operators++) {
		printf("%d - Оператор(ов).\n", operators);
		for (queue_lenght = 0; queue_lenght <= max_op; queue_lenght++) {
			printf("%d - мест(о) в очереди .\n", queue_lenght);
			for (i = 0; i <= operators; i++) {
				sum = sum + pow(A, i) / factorial(i);
			}
			sum = sum + +(1 - pow(A / operators, queue_lenght)) * pow(A, operators + 1) / (factorial(operators) * (operators - A));
			P_0 = 1 / sum;
			P_refuse = P_0 * pow(A, operators + queue_lenght) / (pow(operators, queue_lenght) * factorial(operators));
			printf("Вероятность отказа- %lf.\n", P_refuse);
			for (i = 0; i <= operators; i++) {
				M_op = M_op + i * P_0 * powl(waiting_time, i) / (powl(service_time, i) * factorial(i));
			}
			for (i = 1; i <= queue_lenght; i++) {
				M_op = M_op + operators * P_0 * pow(A, operators + i) / (pow(operators, i) * factorial(operators));
			}
			printf("Мат ожидание числа занятых каналов- %lf.\n", M_op);
			cof = M_op / operators;
			printf("Коэффицент занятости- %lf.\n", cof);
			P_qu = (P_0 * pow(A, operators) * (1 - pow(A / operators, queue_lenght))) / (factorial(operators) * (1 - A / operators));
			printf("Вероятность образования очереди- %lf.\n", P_qu);
			for (i = 1; i <= queue_lenght; i++) {
				M_qu = M_qu + i * P_0 * pow(A, operators + i) / (pow(operators, i) * factorial(operators));
			}
			printf("Мат. ожидание числа ожидающих- %lf.\n", M_qu);
			printf("Коэффициент занятости очереди- %lf.\n\n\n", M_qu / queue_lenght);
		}
		sum = 0;
		M_op = 0;
		M_qu = 0;
	}
}

void task_3(int max_op, double waiting_time, double service_time)
{
	double A = waiting_time / service_time;
	double P_0, P_qu;
	double E = 0.0000001; // для ограничения последовательности
	double count = 1;
	double sum = 0;
	int operators;
	double M_op, M_qu, M_qu0 = 0;
	int i, y;
	double K;
	for (operators = 1; operators <= max_op; operators++)
	{
		printf("Операторов - %d\n", operators);
		for (i = 0; i <= operators; i++)
		{
			sum = sum + pow(A, i) / factorial(i);
		}
		sum = sum + pow(A, operators + 1) / (factorial(operators) * (operators - A));
		P_0 = 1 / sum;
		P_qu = pow(A, operators + 1) * P_0 / (factorial(operators) * (operators - A));
		printf("Вероятность образования очереди - % lf.\n", P_qu);
		for (i = 1; i <= operators; i++)
		{
			M_op = M_op + i * P_0 * pow(A, i) / factorial(i);
		}
		M_op = M_op + operators * P_qu;
		printf("Мат ожидание числа занятых каналов- %lf.\n", M_op);
		K = M_op / operators;
		printf("Коэффицент занятости- %lf.\n", K);
		y = 0;
		while (count > E) {
			y++;
			M_qu = M_qu0 + y * P_0 * pow(A, operators + y) / (pow(operators, y) * factorial(operators));
			count = abs(M_qu - M_qu0);
			M_qu0 = M_qu;
			//printf("y- %d\n", y);
		}
		printf("Мат. ожидание числа ожидающих- %lf.\n\n\n", M_qu);
		// обнуление суммы и прочих
		sum = 0;
		M_op = 0;
		M_qu = 0;
		M_qu0 = 0;
		count = 1;
		y = 0;
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	double service_time = 0.2; // время обслуживания клиента
	double waiting_time = 0.045454545; // время между запросами
	int max=2;
	//max = task_1(waiting_time, service_time);
	task_2(max, waiting_time, service_time);
	//task_3(max, waiting_time, service_time);




}