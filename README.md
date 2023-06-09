# MIPT_FAB_BOT

# Задача

Разработать передвигающегося робота для преодоления полосы препятствий, включающей (в порядке прохождения):
* Бассейн с зефирками
* Эстакаду
* Проезд по тунелю, выход из которого открывается светом
* Лопанье шарика.

Робот не должен быть гусеничным или иметь *абсолютно* круглые колеса. Приветствуется сделать максимально интересного робота.

# Решение

Шагающие машины, несмотря на их интересность, были отвергнуты из-за их сложности в изготовлении и отсутствие гарантии успешного решения задачи в условиях ограниченного времени.

В ходе планирования КБ "Инвалид" было принято реализовать классическую, надежную как швейцарские часы схему с полным приводом, двумя двигателями (по одному на 2 колеса каждой стороны) и жестко закрепленными колесами - поворот осуществляется разностью скоростей на правой и левой стороне.

![engines](https://github.com/LatikovAR/MIPT_FAB_BOT/assets/55430721/e81d7384-02af-4ce9-a4f5-e21cc520d698)

Для преодоления бассейна требовалась большая устойчивость и проходимость. Поэтому центр тяжести был опущен переносом аккумуляторов под днище и установкой больших колес для увеличения дорожного просвета, передаточное отношение двигатель-колесо 1:3.

Колеса из нескольких слоев 3мм фанеры с сапогами на ободе, отсюда одно из рабочих названий - "Пошло поехало". В роли полуосей выступают болты М5. Слоеное колесо зажимается гайками на полуоси. Крепление колес к кузову напечатано на 3D принтере, полуоси в нем фиксируются контргайками так, чтобы свободно вращаться.

Ведомые шестерни располагаются на колесах и зажаты дисками с обеих сторон. Диски фиксируют ведущую шестерню и исключают ее боковые перемещения. Ведущая шестерня вообще говоря может перемещаться по валу двигателя, но держится плотно.

![wheels](https://github.com/LatikovAR/MIPT_FAB_BOT/assets/55430721/2586d790-90be-4f88-b445-bf6a6505c601)

Для увеличения жесткости, кузов сделан двухслойным, верхний слой стоит на стойках на расстоянии от днища. Напечатать стойки не получилось, они были заменены на набор вырезанных из фанеры шайб.

![stoyka](https://github.com/LatikovAR/MIPT_FAB_BOT/assets/55430721/ebb6479e-ed39-429c-901e-2357b14bd89d)

Для открытия туннеля были реализованы огни на светодиодных лентах. А именно: автоматические поворотники и тормозные огни, габариты, включающиеся с пульта фары.

Пульт был собран на макетной плате, без корпуса. Управление осуществлялось двумя джойстиками, каждый управлял "газом" со своей стороны. Нажатия на джойстики активировали фары и пушку.

![IMG_2810](https://github.com/LatikovAR/MIPT_FAB_BOT/assets/55430721/75c29e8c-9b09-4981-937c-82155f5a6814)

Пробитие шарика осуществлялось пушкой. Конструкция основана на таковой у страйкбольных приводов: шестерня с отсутствующими зубьями оттягивает подрезиненную рейку пока зубья не закончатся, после чего рейка отстреливает. На конце рейки закреплено лезвие. В результате испытаний оказалось что PLA не выдерживает таких ударных нагрузок, рейку разрывает и ее кусок отстреливает вместе с лезвием, что добавляет эффектности и поражающей способности. Поэтому рейка была склеена для единственного реального выстрела, с чем справилась.

Крепилась пушка стяжкой из-за нехватки времени. На случай отказа к передней части робота была прикреплена спица из проволоки.

![bfg](https://github.com/LatikovAR/MIPT_FAB_BOT/assets/55430721/0b44059f-0abc-4318-9876-29de04ccb9fa)

![knife](https://github.com/LatikovAR/MIPT_FAB_BOT/assets/55430721/2208abc1-d394-4378-acf4-008ed3c43e58)

# Оборудование и материалы
* Arduino UNO x2 - пульт и "мозги" машины
* Сервопривод постоянного вращения FS5103R - привод шестерни пушки
* Коллекторные двигатели x2 - привод колес
* Motor shield - подключение коллекторных двигателей
* 2x 18650 с блоком - питание
* Адресная светодиодная лента WS281X - огни
* Радио модуль NRF24L01 - передача и прием сигнала
* 3D принтер Creality Ender-3 S1 Pro + PLA - печать креплений колес и двигателей, пушки
* GCC Laser Pro Spirit GLS 4.10 - лазерная резка 3мм фанеры: колеса и корпус.
* Болты M5 - полуоси
* Болты M3x8, M3x50 - крепление двигателей, корпуса, аккумуляторного блока, сборка пушки.

* Freecad, Solidworks - проектирование деталей под 3D печать
* CorelDraw, Inkscape - проектирование деталей под лазерную резку.
