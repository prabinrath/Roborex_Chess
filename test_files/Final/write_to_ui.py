import os
import chess.pgn
#write the pgn data in uci format to a file such that a cpp code can load the moves to the UI afer game retrival from save or crash.
game=chess.pgn.Game()
game.headers["Event"]="Hello"
game.headers["White"]="prabin"
game.headers["Black"]="Stockfish"
game.headers["Round"]="1"
new_text = open("game_write.txt","w")
if(game.headers["Black"]=="Stockfish"):
	tagA="0 ";tagB="1 ";
	new_text.write( game.headers["White"] )
else:
	tagA="1 ";tagB="0 ";
	new_text.write( game.headers["Black"] )
length=len(game.root().variations);
if length>0:
	node = game.root().variations[0];
node_ = game.end();
if length>0:
	while(node.move.uci()!=node_.move.uci()):
		try:
			new_text.write( tagA+node.move.uci()+"\n" )
			node = node.variations[0]
			new_text.write( tagB+node.move.uci()+"\n" )
			node = node.variations[0]
		except:
			pass
new_text.close()
