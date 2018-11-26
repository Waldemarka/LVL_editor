//метод, проверяющий пересекаются ли 2 отрезка [data->p1, data->p2] и [data->p3, data->p4]

int		checkIntersectionOfTwoLineSegments(t_data *data) 
{
	//сначала расставим точки по порядку, т.е. чтобы было data->p1.x <= data->p2.x
	if (data->p2.x < data->p1.x) {
		vector tmp = data->p1;
		data->p1 = data->p2;
		data->p2 = tmp;
	}
	//и data->p3.x <= data->p4.x
	if (data->p4.x < data->p3.x) {
		vector tmp = data->p3;
		data->p3 = data->p4;
		data->p4 = tmp;
	}
	//проверим существование потенциального интервала для точки пересечения отрезков
	if (data->p2.x < data->p3.x) {
		return 0; //ибо у отрезков нету взаимной абсциссы
	}
	//если оба отрезка вертикальные
	if((data->p1.x - data->p2.x == 0) && (data->p3.x - data->p4.x == 0)) {
		//если они лежат на одном X
		if(data->p1.x == data->p3.x) {
			//проверим пересекаются ли они, т.е. есть ли у них общий Y
			//для этого возьмём отрицание от случая, когда они НЕ пересекаются
			if (!((max(data->p1.y, data->p2.y) < min(data->p3.y, data->p4.y)) ||
						(min(data->p1.y, data->p2.y) > max(data->p3.y, data->p4.y)))) {
				return 1;
			}
		}
		return 0;
	}
	//найдём коэффициенты уравнений, содержащих отрезки
	//f1(x) = A1*x + b1 = y
	//f2(x) = A2*x + b2 = y
	//если первый отрезок вертикальный
	if (data->p1.x - data->p2.x == 0) {
		//найдём Xa, Ya - точки пересечения двух прямых
		double Xa = data->p1.x;
		double A2 = (data->p3.y - data->p4.y) / (data->p3.x - data->p4.x);
		double b2 = data->p3.y - A2 * data->p3.x;
		double Ya = A2 * Xa + b2;
		if (data->p3.x <= Xa && data->p4.x >= Xa && min(data->p1.y, data->p2.y) <= Ya &&
				max(data->p1.y, data->p2.y) >= Ya) {
			return 1;
		}
		return 0;
	}
	//если второй отрезок вертикальный
	if (data->p3.x - data->p4.x == 0) {
		//найдём Xa, Ya - точки пересечения двух прямых
		double Xa = data->p3.x;
		double A1 = (data->p1.y - data->p2.y) / (data->p1.x - data->p2.x);
		double b1 = data->p1.y - A1 * data->p1.x;
		double Ya = A1 * Xa + b1;
		if (data->p1.x <= Xa && data->p2.x >= Xa && min(data->p3.y, data->p4.y) <= Ya &&
				max(data->p3.y, data->p4.y) >= Ya) {
			return 1;
		}
		return 0;
	}
	//оба отрезка невертикальные
	double A1 = (data->p1.y - data->p2.y) / (data->p1.x - data->p2.x);
	double A2 = (data->p3.y - data->p4.y) / (data->p3.x - data->p4.x);
	double b1 = data->p1.y - A1 * data->p1.x;
	double b2 = data->p3.y - A2 * data->p3.x;
	if (A1 == A2) {
		return 0; //отрезки параллельны
	}
	//Xa - абсцисса точки пересечения двух прямых
	double Xa = (b2 - b1) / (A1 - A2);
	if ((Xa < max(data->p1.x, data->p3.x)) || (Xa > min( data->p2.x, data->p4.x))) {
		return 0; //точка Xa находится вне пересечения проекций отрезков на ось X
	}
	else {
		return 1;
	}

}
