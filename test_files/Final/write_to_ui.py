import os
import chess.pgn
#write the pgn data in uci format to a file such that a cpp code can load the moves to the UI afer game retrival from save or crash.
game=chess.pgn.readGame()

new_text = open("game_write.txt","w")
node = game.root()
node_ = game.end()

if(game.headers["Black"]=="Stockfish"):
	tagA="0 ";tagB="1 ";
else:
	tagA="1 ";tagB="0 ";
while(node.move.uci()!=node_.move.uci()):
		try:
			new_text.write( tagA+node.move.uci()+"\n" )
			node = node.variations[0]
			new_text.write( tagB+node.move.uci()+"\n" )
			node = node.variations[0]
		except:
			pass
new_text.close()
