Program lab1;

uses unlab1;

var s,s1,s2: string;
	Nom: byte;

begin
	writeln('pass the string');
	readln(s);
	s1 := copy(s, 1, length(s));
	s2 := copy(s, 1, length(s));
	writeln('string before sorting ', s1);
	nom := prov1(s1);
	case nom of
	1: writeln('empty string');
	2: writeln('invalid symbols');
	else
		begin
			sort1(s1);
			writeln('sorted string ', s1);
		end;
	end;

	writeln('string before sorting ', s2);
	nom := prov2(s2);
	case nom of 
	1: writeln('empty string');
	2:writeln('invalid symbols');
	else
		begin
			sort2(s2);
			writeln('sorted string ', s2);
		end;
	end;
end.

