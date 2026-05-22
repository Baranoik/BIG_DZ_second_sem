#=================================================
#				 Сборка базовых файлов (без логов)
Field.o: Field.cpp Field.h constans.h objects/Obj.h Log_config.h
	g++ -I. -Iobjects -c Field.cpp 

Obj.o: objects/Obj.cpp objects/Obj.h element.h constans.h Log_config.h
	g++ -I. -c objects/Obj.cpp -o Obj.o

Player.o: objects/Player.cpp objects/Player.h objects/Obj.h constans.h Log_config.h
	g++ -I. -Iobjects -c objects/Player.cpp -o Player.o

input.o: input.cpp input.h
	g++ -c input.cpp

Obj_manager.o: ObJ_manager.cpp Obj_manager.h Field.h objects/Obj.h Log_config.h
	g++ -I. -Iobjects -c ObJ_manager.cpp -o Obj_manager.o

Obj_fabric.o: Obj_fabric.cpp Obj_fabric.h Field.h objects/Obj.h objects/Chest.h objects/Reward.h objects/Trap.h objects/Entity.h Log_config.h
	g++ -I. -Iobjects -c Obj_fabric.cpp -o Obj_fabric.o

objects/Chest.o: objects/Chest.cpp objects/Chest.h objects/Obj.h Log_config.h
	g++ -I. -c objects/Chest.cpp -o objects/Chest.o

objects/Reward.o: objects/Reward.cpp objects/Reward.h objects/Obj.h element.h Log_config.h
	g++ -I. -c objects/Reward.cpp -o objects/Reward.o

objects/Trap.o: objects/Trap.cpp objects/Trap.h objects/Obj.h element.h Log_config.h
	g++ -I. -c objects/Trap.cpp -o objects/Trap.o

objects/Entity.o: objects/Entity.cpp objects/Entity.h objects/Obj.h element.h Log_config.h
	g++ -I. -c objects/Entity.cpp -o objects/Entity.o

#=================================================
#								 Сборка лог-файлов
Field_loged.o: Field.cpp Field.h constans.h objects/Obj.h Log_config.h
	g++ -I. -Iobjects -c Field.cpp -DLOGQM -o Field_loged.o

Obj_loged.o: objects/Obj.cpp objects/Obj.h element.h constans.h Log_config.h
	g++ -I. -DLOGQM -c objects/Obj.cpp -o Obj_loged.o

Player_loged.o: objects/Player.cpp objects/Player.h objects/Obj.h constans.h Log_config.h
	g++ -I. -Iobjects -c objects/Player.cpp -DLOGQM -o Player_loged.o

input_loged.o: input.cpp input.h
	g++ -c input.cpp -DLOGQM -o input_loged.o

Obj_manager_loged.o: ObJ_manager.cpp Obj_manager.h Field.h objects/Obj.h Log_config.h
	g++ -I. -Iobjects -c ObJ_manager.cpp -DLOGQM -o Obj_manager_loged.o

Obj_fabric_loged.o: Obj_fabric.cpp Obj_fabric.h Field.h objects/Obj.h objects/Chest.h objects/Reward.h objects/Trap.h objects/Entity.h Log_config.h
	g++ -I. -Iobjects -c Obj_fabric.cpp -DLOGQM -o Obj_fabric_loged.o

objects/Chest_loged.o: objects/Chest.cpp objects/Chest.h objects/Obj.h Log_config.h
	g++ -I. -c objects/Chest.cpp -DLOGQM -o objects/Chest_loged.o

objects/Reward_loged.o: objects/Reward.cpp objects/Reward.h objects/Obj.h element.h Log_config.h
	g++ -I. -c objects/Reward.cpp -DLOGQM -o objects/Reward_loged.o

objects/Trap_loged.o: objects/Trap.cpp objects/Trap.h objects/Obj.h element.h Log_config.h
	g++ -I. -c objects/Trap.cpp -DLOGQM -o objects/Trap_loged.o

objects/Entity_loged.o: objects/Entity.cpp objects/Entity.h objects/Obj.h element.h Log_config.h
	g++ -I. -c objects/Entity.cpp -DLOGQM -o objects/Entity_loged.o

#=================================================
# 									 Сборка тестов
test_01b.o: tests/test_01b.cpp Field.h objects/Obj.h objects/Player.h Obj_manager.h Obj_fabric.h
	g++ -I. -Iobjects -c tests/test_01b.cpp -DLOGQM -o test_01b.o

test_02.o: tests/test_02.cpp Field.h objects/Obj.h objects/Player.h constans.h Obj_manager.h Obj_fabric.h
	g++ -I. -Iobjects -c tests/test_02.cpp -DLOGQM -o test_02.o

test_02b.o: tests/test_02b.cpp objects/Obj.h element.h constans.h Log_config.h
	g++ -I. -Iobjects -c tests/test_02b.cpp -DLOGQM -o test_02b.o

test_03a.o: tests/test_03a.cpp Field.h objects/Obj.h Obj_manager.h Obj_fabric.h Log_config.h
	g++ -I. -Iobjects -c tests/test_03a.cpp -DLOGQM -o test_03a.o

#=================================================
#								   Линковка тестов
test_01b: test_01b.o Field_loged.o Obj_loged.o Player_loged.o  Obj_manager_loged.o Obj_fabric_loged.o objects/Chest_loged.o objects/Reward_loged.o objects/Trap_loged.o objects/Entity_loged.o
	g++ test_01b.o Field_loged.o Obj_loged.o Player_loged.o  Obj_manager_loged.o Obj_fabric_loged.o objects/Chest_loged.o objects/Reward_loged.o objects/Trap_loged.o objects/Entity_loged.o -o test_01b

test_02: test_02.o Field_loged.o Obj_loged.o Player_loged.o  Obj_manager_loged.o Obj_fabric_loged.o objects/Chest_loged.o objects/Reward_loged.o objects/Trap_loged.o objects/Entity_loged.o
	g++ test_02.o Field_loged.o Obj_loged.o Player_loged.o  Obj_manager_loged.o Obj_fabric_loged.o objects/Chest_loged.o objects/Reward_loged.o objects/Trap_loged.o objects/Entity_loged.o -o test_02

test_02b: test_02b.o Obj_loged.o
	g++ test_02b.o Obj_loged.o -o test_02b

test_03a: test_03a.o Field_loged.o Obj_loged.o Player_loged.o  Obj_manager_loged.o Obj_fabric_loged.o objects/Chest_loged.o objects/Reward_loged.o objects/Trap_loged.o objects/Entity_loged.o
	g++ test_03a.o Field_loged.o Obj_loged.o Player_loged.o  Obj_manager_loged.o Obj_fabric_loged.o objects/Chest_loged.o objects/Reward_loged.o objects/Trap_loged.o objects/Entity_loged.o -o test_03a

#=================================================
#									  тестирования
T01b: test_01b
	./test_01b

T02: test_02
	./test_02

T02b: test_02b
	./test_02b

T03a: test_03a
	./test_03a

#=================================================
#										   Очистка 
clean:
	rm -f *.o objects/*.o test_01b test_02 test_02b test_03a
