#=================================================
#				 Сборка базовых файлов (без логов)
Field.o: Field.cpp Field.h constans.h Obj.h Log_config.h
	g++ -c Field.cpp 

Obj.o: Obj.cpp Obj.h
	g++ -c Obj.cpp

Player.o: Player.cpp Player.h Obj.h constans.h Log_config.h
	g++ -c Player.cpp -o Player.o

#=================================================
#								 Сборка лог-файлов
Field_loged.o: Field.cpp Field.h constans.h Obj.h Log_config.h
	g++ -c Field.cpp -DLOGQM -o Field_loged.o

Obj_loged.o: Obj.cpp Obj.h Log_config.h
	g++ -c Obj.cpp -DLOGQM -o Obj_loged.o

Player_loged.o: Player.cpp Player.h Obj.h constans.h Log_config.h
	g++ -c Player.cpp -DLOGQM -o Player_loged.o

#=================================================
# 									 Сборка тестов
test_01b.o: test_01b.cpp Field.h Obj.h Player.h
	g++ -c test_01b.cpp -DLOGQM -o test_01b.o

test_02.o: test_02.cpp Field.h Obj.h Player.h constans.h
	g++ -c test_02.cpp -DLOGQM -o test_02.o

test_02b.o: test_02b.cpp Obj.h element.h constans.h Log_config.h
	g++ -c test_02b.cpp -DLOGQM -o test_02b.o

#=================================================
#								   Линковка тестов
test_01b: test_01b.o Field_loged.o Obj_loged.o Player_loged.o
	g++ test_01b.o Field_loged.o Obj_loged.o Player_loged.o -o test_01b

test_02: test_02.o Field_loged.o Obj_loged.o Player_loged.o
	g++ test_02.o Field_loged.o Obj_loged.o Player_loged.o -o test_02

test_02b: test_02b.o Obj_loged.o
	g++ test_02b.o Obj_loged.o -o test_02b

#=================================================
#									  тестирования
T01b: test_01b
	./test_01b

T02: test_02
	./test_02

# тест эффектов
T02b: test_02b
	./test_02b

#=================================================
#										   Очистка 
clean:
	rm -f *.o test_01b test_02 test_02b
