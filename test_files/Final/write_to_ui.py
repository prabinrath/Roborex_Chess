import os
import chess.pgn

game=chess.pgn.readGame()

new_text = open("game_write.txt")
node = game.root()
node_ = game.end()

if(game.headers["Black"]=="Stockfish"):
	while(node.move.uci()!=node_.move.uci()):
		node = node.variations[0]
		new_text.write("0 "+node.move.uci())
		node = node.variations[0]
		new_text.write("1 "+node.move.uci())
	new_text.close()

else:
	while(node.move.uci()!=node_.move.uci()):
		node = node.variations[0]
		new_text.write("1 "+node.move.uci())
		node = node.variations[0]
		new_text.write("0 "+node.move.uci())
	new_text.close()