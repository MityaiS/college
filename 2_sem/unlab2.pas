Unit unlab2;
{$MODE DELPHI}

interface 

type 
	creatures = (vampire, werewolf, zombie);
	monster = record
		name: string[20];
		birthday: string[11];
		c_type: creatures;
	end;

Procedure Createtypedfile1();
Procedure Createtypedfile2();
Procedure Find_Swap();
Procedure ViewFile();

Implementation 

Procedure Createtypedfile1();
var
	creature: monster;
	fr: file of monster;
	count, n: integer;
	ch: char;
	fname:string[80];
begin
	if ParamCount < 1 then 
	begin
		writeln('Too less parameters:(');
		exit
	end;
	fname := ParamStr(1);
	assign(fr, fname);
	try 
		rewrite(fr);
	Except
		writeln('I am sorry, I could not create ', Paramstr(1), ', please try again, if you will not accomplish this, you are loser!!!(this is easy)');
		exit
	end;
	count := 0;
	repeat 
		write('Your name?');
		readln(creature.name);
		write('Your birthday?');
		readln(creature.birthday);
		write('What type of crature are you(0-vampire, 1-werewolf, 2-zombie)');
		readln(n);
		creature.c_type := creatures(n);

		write(fr, creature);
		inc(count);
		write('Is there anyone else?(y/n)');
		readln(ch)
	until upcase(ch) = 'N';
	CloseFile(fr);
	writeln('We made this file of ', count,'records');
end;

Procedure CreateTypedFile2();
var 
	creature: monster;
	fr: textfile;
	ft: file of monster;
	count, n: integer;
	fnamer, fnamet:string[80];
begin
	if ParamCount < 2 then 
	begin
		writeln('Too less paramenters');
		exit
	end;

	fnamet := Paramstr(1);
	assign(ft, fnamet);
	try rewrite(ft);
	except
		writeln('Common, what is wrong with you, we couldn not create ', Paramstr(1));
		exit
	end;
	fnamer := Paramstr(2);
	assign(fr, fnamer);
	try reset(fr);
	except
		writeln('Common, what is wrong with you, we couldn not read ', Paramstr(2));
		exit
	end;
	count := 0;

	while not eof(fr) do 
	begin 
		count += 1;
		readln(fr, creature.name);
		readln(fr, creature.birthday);
		readln(fr, n);
		creature.c_type := creatures(n);
		write(creature.name, ' ');
		write(creature.birthday, ' ');
		writeln(creature.c_type);

		write(ft, creature);
	end;
	closefile(fr);
	Closefile(ft);
	if count = 0 then 
		writeln('There was no records in source file')
	else
		writeln('We made a file with ', count, ' records.');
end;

Procedure Find_Swap();
var 
	creature, creature_a, creature_b: monster;
	fr: file of monster;
	count_a, count_b, k: integer;
	fname:string[80];
begin
	if Paramcount < 1 then 
	begin
		writeln('Too less parametres');
		exit
	end;
	Fname := Paramstr(1);
	assign(fr, fname);
	try reset(fr);
	except
		writeln('We failed to open ', fname);
		exit
	end;
	writeln('Wich record do you want to replace with?');
	readln(k);
	while (k<1) or (k>filesize(fr)) do 
	begin
		writeln('There is no such record. Try again.');
		readln(k);
	end;
	count_a := 0;
	count_b := 0;
	while not eof(fr) and ((count_a = 0) or (count_b = 0)) do
	begin
		read(fr, creature);
		if (creature.name[1]) = 'M' then 
		begin	
			writeln('We found ', creature.c_type, ' ', creature.name, ' ',
					creature.birthday);
			creature_a := creature;
			count_a := filepos(fr);
		end;
		if filepos(fr) = k then 
		begin
			creature_b := creature;
			count_b := filepos(fr);
		end;
	end;
	if ((count_a = 0) or (count_b = 0)) then 
		writeln('Data of your request not found')
	else
	begin
		writeln('We swaped two records');
		seek(fr, count_a-1);
		write(fr, creature_b);
		seek(fr, count_b-1);
		write(fr, creature_a);
		write(count_a, ' ', count_b);
	end;

	closefile(fr);
end;

Procedure Viewfile();
var
	creature: monster;
	fr: file of monster;
	count: integer;
	fname: string[80];
begin
	if paramcount < 1 then 
	begin 
		writeln('Too less parametres');
		exit
	end;

	fname := paramstr(1);
	assign(fr, fname);
	try reset(fr);
	except
		writeln('We could not open file ', Fname);
		exit
	end;
	count := 0;
	while not eof(fr) do 
	begin
		read(fr, creature);
		writeln('We found ',creature.c_type, ' ', creature.name, ' ', creature.birthday);
		inc(count);
	end;
	if count = 0 then 
		writeln('We did not found any records')
	else
		writeln('We found ',count, ' records');
	closefile(fr);
end;
end.

