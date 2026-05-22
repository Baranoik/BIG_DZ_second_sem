#=================================================
#				 Сборка базовых файлов (без логов)
Field.o: Field.cpp Field.h constans.h objects/Obj.h Log_config.h
	g++ -Iobjects -c Field.cpp 

Obj.o: objects/Obj.cpp objects/Obj.h element.h constans.h Log_config.h
	g++ -I. -c objects/Obj.cpp -o Obj.o

Player.o: Player.cpp Player.h objects/Obj.h constans.h Log_config.h
	g++ -Iobjects -c Player.cpp -o Player.o

input.o: input.cpp input.h
	g++ -c input.cpp

Obj_manager.o: ObJ_manager.cpp Obj_manager.h Field.h objects/Obj.h Log_config.h
	g++ -Iobjects -c ObJ_manager.cpp -o Obj_manager.o

Obj_fabric.o: Obj_fabric.cpp Obj_fabric.h Field.h objects/Obj.h objects/Chest.h objects/Reward.h objects/Trap.h objects/Enemy.h Log_config.h
	g++ -Iobjects -c Obj_fabric.cpp -o Obj_fabric.o

objects/Chest.o: objects/Chest.cpp objects/Chest.h objects/Obj.h Log_config.h
	g++ -I. -c objects/Chest.cpp -o objects/Chest.o

objects/Reward.o: objects/Reward.cpp objects/Reward.h objects/Obj.h element.h Log_config.h
	g++ -I. -c objects/Reward.cpp -o objects/Reward.o

objects/Trap.o: objects/Trap.cpp objects/Trap.h objects/Obj.h element.h Log_config.h
	g++ -I. -c objects/Trap.cpp -o objects/Trap.o

objects/Enemy.o: objects/Enemy.cpp objects/Enemy.h objects/Obj.h element.h Log_config.h
	g++ -I. -c objects/Enemy.cpp -o objects/Enemy.o

#=================================================
#								 Сборка лог-файлов
Field_loged.o: Field.cpp Field.h constans.h objects/Obj.h Log_config.h
	g++ -Iobjects -c Field.cpp -DLOGQM -o Field_loged.o

Obj_loged.o: objects/Obj.cpp objects/Obj.h element.h constans.h Log_config.h
	g++ -I. -DLOGQM -c objects/Obj.cpp -o Obj_loged.o

Player_loged.o: Player.cpp Player.h objects/Obj.h constans.h Log_config.h
	g++ -Iobjects -c Player.cpp -DLOGQM -o Player_loged.o

input_loged.o: input.cpp input.h
	g++ -c input.cpp -DLOGQM -o input_loged.o

Obj_manager_loged.o: ObJ_manager.cpp Obj_manager.h Field.h objects/Obj.h Log_config.h
	g++ -Iobjects -c ObJ_manager.cpp -DLOGQM -o Obj_manager_loged.o

Obj_fabric_loged.o: Obj_fabric.cpp Obj_fabric.h Field.h objects/Obj.h objects/Chest.h objects/Reward.h objects/Trap.h objects/Enemy.h Log_config.h
	g++ -Iobjects -c Obj_fabric.cpp -DLOGQM -o Obj_fabric_loged.o

objects/Chest_loged.o: objects/Chest.cpp objects/Chest.h objects/Obj.h Log_config.h
	g++ -I. -c objects/Chest.cpp -DLOGQM -o objects/Chest_loged.o

objects/Reward_loged.o: objects/Reward.cpp objects/Reward.h objects/Obj.h element.h Log_config.h
	g++ -I. -c objects/Reward.cpp -DLOGQM -o objects/Reward_loged.o

objects/Trap_loged.o: objects/Trap.cpp objects/Trap.h objects/Obj.h element.h Log_config.h
	g++ -I. -c objects/Trap.cpp -DLOGQM -o objects/Trap_loged.o

objects/Enemy_loged.o: objects/Enemy.cpp objects/Enemy.h objects/Obj.h element.h Log_config.h
	g++ -I. -c objects/Enemy.cpp -DLOGQM -o objects/Enemy_loged.o

#=================================================
# 									 Сборка тестов
# Предугаданная ошибка устранена: добавлены флаги -I. и -Iobjects для ВСЕХ тестов
test_01b.o: tests/test_01b.cpp Field.h objects/Obj.h Player.h Obj_manager.h Obj_fabric.h
	g++ -I. -Iobjects -c tests/test_01b.cpp -DLOGQM -o test_01b.o

test_02.o: tests/test_02.cpp Field.h objects/Obj.h Player.h constans.h Obj_manager.h Obj_fabric.h
	g++ -I. -Iobjects -c tests/test_02.cpp -DLOGQM -o test_02.o

test_02b.o: tests/test_02b.cpp objects/Obj.h element.h constans.h Log_config.h
	g++ -I. -Iobjects -c tests/test_02b.cpp -DLOGQM -o test_02b.o

#=================================================
#								   Линковка тестов
test_01b: test_01b.o Field_loged.o Obj_loged.o Player_loged.o input_loged.o Obj_manager_loged.o Obj_fabric_loged.o objects/Chest_loged.o objects/Reward_loged.o objects/Trap_loged.o objects/Enemy_loged.o
	g++ test_01b.o Field_loged.o Obj_loged.o Player_loged.o input_loged.o Obj_manager_loged.o Obj_fabric_loged.o objects/Chest_loged.o objects/Reward_loged.o objects/Trap_loged.o objects/Enemy_loged.o -o test_01b

test_02: test_02.o Field_loged.o Obj_loged.o Player_loged.o input_loged.o Obj_manager_loged.o Obj_fabric_loged.o objects/Chest_loged.o objects/Reward_loged.o objects/Trap_loged.o objects/Enemy_loged.o
	g++ test_02.o Field_loged.o Obj_loged.o Player_loged.o input_loged.o Obj_manager_loged.o Obj_fabric_loged.o objects/Chest_loged.o objects/Reward_loged.o objects/Trap_loged.o objects/Enemy_loged.o -o test_02

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
	rm -f *.o objects/*.o test_01b test_02 test_02b
