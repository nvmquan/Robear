# On definit les r�pertoires de chaques types d'elements
NAME_PROG=Programme
OBJ_DIR = objects
SOURCES_DIR = sources
HEADERS_DIR = headers
CFLAG = -lrt -std=c++0x
CC = g++

$(NAME_PROG): $(OBJ_DIR)/main.o $(OBJ_DIR)/strategie.o  $(OBJ_DIR)/deplacement.o $(OBJ_DIR)/detecter.o  $(OBJ_DIR)/calculer_odometrie.o $(OBJ_DIR)/comMoteur.o  $(OBJ_DIR)/encoders.o $(OBJ_DIR)/eqep.o $(OBJ_DIR)/get_file_name.o $(OBJ_DIR)/protocole_com_serie.o $(OBJ_DIR)/serial_com.o $(OBJ_DIR)/serialib.o $(OBJ_DIR)/commandes_actionneurs.o
			$(CC) $(OBJ_DIR)/main.o $(OBJ_DIR)/strategie.o   $(OBJ_DIR)/deplacement.o $(OBJ_DIR)/detecter.o  $(OBJ_DIR)/calculer_odometrie.o  $(OBJ_DIR)/comMoteur.o $(OBJ_DIR)/encoders.o $(OBJ_DIR)/eqep.o $(OBJ_DIR)/get_file_name.o $(OBJ_DIR)/protocole_com_serie.o $(OBJ_DIR)/serial_com.o $(OBJ_DIR)/serialib.o $(OBJ_DIR)/commandes_actionneurs.o -o $(NAME_PROG) -lpthread

$(OBJ_DIR)/main.o: $(SOURCES_DIR)/main.cpp $(HEADERS_DIR)/eqep.h $(HEADERS_DIR)/protocole_com_serie.h $(HEADERS_DIR)/comMoteur.h $(HEADERS_DIR)/calculer_odometrie.h $(HEADERS_DIR)/commandes_actionneurs.h $(HEADERS_DIR)/strategie.h $(HEADERS_DIR)/deplacement.h
			$(CC) -o $(OBJ_DIR)/main.o -c $(SOURCES_DIR)/main.cpp $(CFLAG)

$(OBJ_DIR)/calculer_odometrie.o: $(SOURCES_DIR)/calculer_odometrie.cpp $(HEADERS_DIR)/calculer_odometrie.h $(HEADERS_DIR)/eqep.h
						$(CC) -o $(OBJ_DIR)/calculer_odometrie.o -c $(SOURCES_DIR)/calculer_odometrie.cpp $(CFLAG)

$(OBJ_DIR)/commandes_actionneurs.o: $(SOURCES_DIR)/commandes_actionneurs.cpp $(HEADERS_DIR)/comMoteur.h $(HEADERS_DIR)/protocole_com_serie.h $(HEADERS_DIR)/commandes_actionneurs.h $(HEADERS_DIR)/calculer_odometrie.h
									$(CC) -o $(OBJ_DIR)/commandes_actionneurs.o -c $(SOURCES_DIR)/commandes_actionneurs.cpp $(CFLAG)

$(OBJ_DIR)/comMoteur.o: $(SOURCES_DIR)/comMoteur.cpp $(HEADERS_DIR)/comMoteur.h $(HEADERS_DIR)/protocole_com_serie.h
			$(CC) -o $(OBJ_DIR)/comMoteur.o -c $(SOURCES_DIR)/comMoteur.cpp $(CFLAG)

$(OBJ_DIR)/deplacement.o: $(SOURCES_DIR)/deplacement.cpp $(HEADERS_DIR)/deplacement.h $(HEADERS_DIR)/comMoteur.h $(HEADERS_DIR)/protocole_com_serie.h $(HEADERS_DIR)/calculer_odometrie.h $(HEADERS_DIR)/detecter.h
						$(CC) -o $(OBJ_DIR)/deplacement.o -c $(SOURCES_DIR)/deplacement.cpp $(CFLAG)

$(OBJ_DIR)/detecter.o: $(SOURCES_DIR)/detecter.cpp $(HEADERS_DIR)/detecter.h $(HEADERS_DIR)/comMoteur.h $(HEADERS_DIR)/protocole_com_serie.h $(HEADERS_DIR)/calculer_odometrie.h $(HEADERS_DIR)/get_file_name.h $(HEADERS_DIR)/serialib.h $(HEADERS_DIR)/serial_com.h $(HEADERS_DIR)/commandes_actionneurs.h
												$(CC) -o $(OBJ_DIR)/detecter.o -c $(SOURCES_DIR)/detecter.cpp $(CFLAG)

$(OBJ_DIR)/encoders.o: $(SOURCES_DIR)/encoders.cpp $(HEADERS_DIR)/encoders.h $(HEADERS_DIR)/get_file_name.h
			$(CC) -o $(OBJ_DIR)/encoders.o -c $(SOURCES_DIR)/encoders.cpp $(CFLAG)

$(OBJ_DIR)/eqep.o: $(SOURCES_DIR)/eqep.cpp $(HEADERS_DIR)/eqep.h $(HEADERS_DIR)/encoders.h
			$(CC) -o $(OBJ_DIR)/eqep.o -c $(SOURCES_DIR)/eqep.cpp $(CFLAG)

$(OBJ_DIR)/get_file_name.o: $(SOURCES_DIR)/get_file_name.cpp $(HEADERS_DIR)/get_file_name.h
			$(CC) -o $(OBJ_DIR)/get_file_name.o -c $(SOURCES_DIR)/get_file_name.cpp $(CFLAG)

$(OBJ_DIR)/protocole_com_serie.o: $(SOURCES_DIR)/protocole_com_serie.cpp $(HEADERS_DIR)/protocole_com_serie.h $(HEADERS_DIR)/serialib.h
			$(CC) -o $(OBJ_DIR)/protocole_com_serie.o -c $(SOURCES_DIR)/protocole_com_serie.cpp $(CFLAG)

$(OBJ_DIR)/serial_com.o: $(SOURCES_DIR)/serial_com.cpp $(HEADERS_DIR)/serial_com.h $(HEADERS_DIR)/get_file_name.h
			$(CC) -o $(OBJ_DIR)/serial_com.o -c $(SOURCES_DIR)/serial_com.cpp $(CFLAG)

$(OBJ_DIR)/serialib.o: $(SOURCES_DIR)/serialib.cpp $(HEADERS_DIR)/serialib.h $(HEADERS_DIR)/serial_com.h
			$(CC) -o $(OBJ_DIR)/serialib.o -c $(SOURCES_DIR)/serialib.cpp $(CFLAG)

$(OBJ_DIR)/strategie.o: $(SOURCES_DIR)/strategie.cpp $(HEADERS_DIR)/strategie.h $(HEADERS_DIR)/calculer_odometrie.h $(HEADERS_DIR)/comMoteur.h $(HEADERS_DIR)/protocole_com_serie.h $(HEADERS_DIR)/eqep.h $(HEADERS_DIR)/commandes_actionneurs.h $(HEADERS_DIR)/detecter.h $(HEADERS_DIR)/deplacement.h
												$(CC) -o $(OBJ_DIR)/strategie.o -c $(SOURCES_DIR)/strategie.cpp $(CFLAG)
