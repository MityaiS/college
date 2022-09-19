program lab2;
{$MODE DELPHI}

uses 
unlab2;

var 
	ch:char;
	chs:string;
begin
	repeat
		writeln('--------------------------------------'); 
		writeln('D - make new file in dialog'); 
		writeln('N - make from text file'); 
		writeln('F - find and swap'); 
		writeln('V - view'); 
		writeln('E - the end of the whole process'); 
		write('What do you desire, my sir?'); 
		if ParamCount > 2 then 
		begin
			chs := Paramstr(3);
			ch := chs[1];
		end	
		else
			readln(ch);
		writeln('--------------------------------------'); 
		ch:= UpCase(ch);
		case ch of 
			'D': CreateTypedFile1;
			'N': CreateTypedFile2; 
			'F': Find_Swap; 
			'V': ViewFile; 
			'E': exit; 
		else 
		begin 
			writeln('My lord, the command you typed is not correct, please try again'); 
		end; 
		end; 
		if ParamCount > 2 then
			exit;
	until ch = 'E'; 
end. 
