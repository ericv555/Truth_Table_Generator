CFLAGS = -g -W -pedantic -std=gnu++20
INCLUDE_PATH = "./boost_1_82_0"

FILES = Parser.cpp Node.cpp Errorhandling.cpp Lexer.cpp Evaluator.cpp Main.cpp


all:
	g++ $(CFLAGS) -I$(INCLUDE_PATH) $(FILES) -o proof_checker