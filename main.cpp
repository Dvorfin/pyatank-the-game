#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <cmath>


#define PI 3.14159265 

using namespace sf;
using namespace std;


int main()
{
	
	RenderWindow window(VideoMode(800, 900), "PYATANK THE GAME", Style::Close);  
	Font font;
	font.loadFromFile("C:/Windows/Fonts/calibri.ttf");

	int dist, angle = 0, V0 = 0, g = 10, x = 390, y1 = 800, y2 = 800, count1 = 0, count2 = 0;
	double Vx, S = 0, flyTime;
	int T = 0;
	bool buttonPressed = 0;
	bool winTxt = 0;
	bool check1 = 0, check2 =0;
	bool movementStop = 0;
	bool Player = 0;
	bool victory = 0;
	string str, str2, dist1, dist2, whoWon;
	string points;
	

	srand(time(NULL));  
	int distance = (rand() % 100);
	dist = 840 - (distance + 500); // из расстоняния от верхней грани окна до центра шара вычитаем рандомное смещение и высотку поля
	string strD = "Distance: " + to_string(dist);

	while (window.isOpen())		// главный цикл. выполняется, пока открыто окно
	{
		
		Text txtD, txtScore1, txtScore2, tAngle, tVelocity, tWon, txtPoints;

		
		

		Event event;		// Обрабатываем очередь событий в цикле
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)	// если нажат крестик 
				window.close();		// то закрываем окно
		
			

			if (event.type == Event::KeyPressed) {
				if ((event.key.code == Keyboard::Left)) {
				//	angle = stoi(str);  // преобразование строки в int 
					cout << "Angle: " << angle << endl;
					if (angle < 90) {
						angle++;
					}
					str = "Angle: " + to_string(angle);  // переводим инт в строку
				//	str.clear();
					
				} else if ((event.key.code == Keyboard::Right)) {
					cout << "Angle: " << angle << endl;
					if (angle > 0) {
						angle--;
					}	
					str = "Angle: " +  to_string(angle);
				} else if ((event.key.code == Keyboard::Up)) {
					cout << "V0: " << V0 << endl;
					V0++;
					str2 = "V0: " + to_string(V0);
				} else if ((event.key.code == Keyboard::Down)) {
					cout << "V0: " << V0 << endl;
					if (V0 > 0) {
						V0--;
					}
					str2 = "V0: " + to_string(V0);
					
				}
				else if (event.key.code == Keyboard::Enter) {
					buttonPressed = 1;
					str.clear();
					str2.clear();
					
					
					
				}
			
					
				
			}

		}

		
		this_thread::sleep_for(std::chrono::milliseconds(16));
		window.clear(Color(175, 180, 240, 0));	// Отрисовка окна


		tWon.setFont(font);
		tWon.setPosition(250, 100);
		tWon.setString(whoWon);
		tWon.setCharacterSize(45);
		tWon.setStyle(Text::Bold);
		

		RectangleShape field(Vector2f(600.f, 500.f));   // создаём прямоугольник размером 600 х 500
		field.move(100, distance);   // перемещаем прямоугольник
		field.setFillColor(Color(20, 120, 100));	// устанавливаем ему цвет
		window.draw(field);		// отрисовка прямоугольника

		CircleShape ball(10.f);   // мячик 1 игрока
		ball.setFillColor(Color(25, 63, 63));
		ball.setOutlineThickness(2.f); // устанавливаем толщину контура круга
		ball.setOutlineColor(Color(255, 182, 193)); // устанавливаем цвет контура

		CircleShape ball2(10.f);   // мячик 2 игрока
		ball2.setFillColor(Color(50, 60, 120));
		ball2.setOutlineThickness(2.f); // устанавливаем толщину контура круга
		ball2.setOutlineColor(Color(255, 182, 193)); // устанавливаем цвет контура

		
		if (buttonPressed) {   // если введен угол и начальная скорость

			flyTime = (V0*V0*sin(2 * angle * PI / 180)) / g;   // вычисляем время полета шара


			if (T < flyTime) {		// пока время движения шара мегьше времени полета шара
				T++;
				Vx = cos(angle * PI / 180)*V0;		// вычисляем скорость и пройденный путь для отрисовки перемещения
				S = (Vx * T)/10;
				if (Player) {
					y2 = y2 - S;
					check2 = 1;
					
				}
				else {
					y1 = y1 - S;
					check1 = 1;
				}
				S = 0;
			}
			else {  // если шарик остановился
				buttonPressed = 0;		
				Player = 1;
				T = 0;
				Vx = 0;
				S = 0;
				flyTime = 0;
				angle = 0;
				V0 = 0;
			}

			
			cout << Player << endl;
		
		}


		ball2.move(x, (y2 - S));  // перемещение шариков
		ball.move(x, (y1 - S));
		
		
		if (Player) { // прочет расстояния до кошонета и его вывод на экран

			cout << "y1: " << abs(distance + 243 - abs(y1)) << "  y2: " << abs(distance + 243 - abs(y2)) << endl;
			dist2 = "Second player dist: " + to_string(abs(distance + 243 - abs(y2)));

		} else  {

			dist1 = "First player dist: " + to_string(abs(distance + 243 - abs(y1)));
			dist2 = "Second player dist: " + to_string(abs(distance + 243 - abs(y2)));

		}
		


		if (check1 && check2) { // если оба шарика были брошены

			if ((abs(distance + 243 - abs(y2)) > abs(distance + 243 - abs(y1)))) {
				cout << "First player win";
				whoWon = "First player win";
			}
			else {
				cout << "Second player win";
				whoWon = "Second player win";
			}

			
			if (V0 <= 0) {
				this_thread::sleep_for(std::chrono::milliseconds(160));
				Player = 0;
				S = 0;
				
				check1 = 0;
				check2 = 0;

				if ((abs(distance + 243 - abs(y2)) > abs(distance + 243 - abs(y1)))) { // вычисляем, кто ближе попал и добавляем очко
					count1++;
				}
				else {
					count2++;
				}

				y1 = 800;
				y2 = 800;
			}
			

		}
		
		if ((count1 == 3 || count2 == 3)) {   // если отыграли 3 раунда
			
			count1 = 0;
			count2 = 0;
			winTxt = 1;

		}

		if (winTxt) {

			window.draw(tWon);  // отрисовка текста победы
			window.display(); // обновление экрана для вывода текста
			this_thread::sleep_for(std::chrono::milliseconds(2000));
			winTxt = 0;

		}

		
		
		string strD = "Distance: " + to_string(dist);
		points = "Points: " +  to_string(count1) + "  " + to_string(count2);


		CircleShape circle(20.f); // место броска игрока
		circle.setFillColor(Color(209, 95, 238));
		circle.setOutlineThickness(5.f); // Устанавливаем толщину контура круга
		circle.setOutlineColor(Color(255, 182, 193)); // Устанавливаем цвет контура
		circle.move(380, 800);

		
		CircleShape cochonnet(7.f);   // кошоннет
		cochonnet.setFillColor(Color(205, 133, 63));
		cochonnet.setOutlineThickness(2.f); // Устанавливаем толщину контура круга
		cochonnet.setOutlineColor(Color(255, 182, 193)); // Устанавливаем цвет контура
		cochonnet.move(393, distance+243);
		window.draw(cochonnet);


		RectangleShape textSpace1(Vector2f(280.f, 100.f));  // прямогугольник для текста
		textSpace1.move(20, 780);
		textSpace1.setFillColor(Color(128, 128, 128));
		window.draw(textSpace1);

		RectangleShape textSpace2(Vector2f(280.f, 100.f));  // прямогугольник для второго текста
		textSpace2.move(500, 780);
		textSpace2.setFillColor(Color(128, 128, 128));
		window.draw(textSpace2);
		
		RectangleShape line_with_thickness(Vector2f(130.f, 5.f));		// Линия с заданной толщиной
		line_with_thickness.move(335, 845);		// Перемещаем линию в нижний ряд справа от прямоугольника
		window.draw(line_with_thickness);		// Отрисовка линии
		
		
		// текст
		txtPoints.setFont(font);
		txtD.setFont(font);
		txtScore1.setFont(font);
		txtScore2.setFont(font);
		tAngle.setFont(font);
		tVelocity.setFont(font);
		
		
		// устанавливаем позицию текста
		txtPoints.setPosition(510, 840);
		txtD.setPosition(30, 780);
		txtScore1.setPosition(30, 810);
		txtScore2.setPosition(30, 840);
		tAngle.setPosition(510, 780);
		tVelocity.setPosition(510, 810);
		

		// помещаем текст 
		txtPoints.setString(points);
		txtD.setString(strD);
		txtScore1.setString(dist1);
		txtScore2.setString(dist2);
		tAngle.setString(str);
		tVelocity.setString(str2);
		

		// размер текста
		txtPoints.setCharacterSize(25);
		txtD.setCharacterSize(25);
		txtScore1.setCharacterSize(25);
		txtScore2.setCharacterSize(25);
		tAngle.setCharacterSize(25);
		tVelocity.setCharacterSize(25);
		

		// жирный текст
		txtPoints.setStyle(Text::Bold);
		txtD.setStyle(Text::Bold);
		txtScore1.setStyle(Text::Bold);
		txtScore2.setStyle(Text::Bold);
		tAngle.setStyle(Text::Bold);
		tVelocity.setStyle(Text::Bold);
		
		
		// отрисовка текстов
		window.draw(txtPoints);
		window.draw(txtD);
		window.draw(txtScore1);
		window.draw(txtScore2);
		window.draw(tAngle);
		window.draw(tVelocity);
		
		
		window.draw(ball);
		window.draw(ball2);
		window.draw(circle);
		

		window.display();
		
	}

	return 0;
}
