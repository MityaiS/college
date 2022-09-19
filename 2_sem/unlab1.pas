unit unlab1;
interface 

const
	symbtable = '0123456789zyxwvutsrqponmlkjihgfedcbaABCDEFGHIJKLMNOPQRSTUVWXYZ';
	nums: set of '0' .. '9' = ['0'..'9'];
	rev_lat: set of char = ['a'..'z'];
	big_lat: set of char = ['A'..'Z'];

function prov1(const s:string): byte;
function prov2(const s:string): byte;
procedure sort1(var s:string);
procedure sort2(var s:string);

implementation

function prov1(const s:string): byte;
var 
	nom: byte;
	i, len:word;
begin
	nom := 0;
	len := length(s);
	if len = 0 then nom := 1
	else
		begin
			i := 1;
			while (i <= len) and (nom = 0) do 
			begin
				if not ((s[i] in nums) or (s[i] in rev_lat)
				or (s[i] in big_lat)) then nom := 2;
				inc(i);
			end;
		end;
	prov1 := nom;
end;

function prov2(const s:string): byte;
var 
	nom:byte;
	i,len:word;
begin
	nom := 0;
	len := length(s);
	if len = 0 then nom := 1
	else
	begin
		i := 1;
		while (i <= len) and (nom = 0) do
		begin
			if not(pos(s[i], symbtable) > 0) then nom := 2;
			inc(i);
		end;
	end;
	prov2 := nom;
end;

procedure sort1(var s:string);
var
	i, z, len:word;
	flag: boolean;
	ch: char;
begin
	z := 1;
	len := length(s);
	repeat 
		flag := true;
		for i := 1 to len - z do
			if (s[i] in big_lat) and ((s[i+1] in nums) or (s[i+1] in rev_lat)) or
			(s[i] in rev_lat) and (s[i+1] in nums) or
			(s[i] in nums) and (s[i+1] in nums) and (s[i]>s[i+1]) or
			(s[i] in rev_lat) and (s[i+1] in rev_lat) and (s[i]<s[i+1]) or
			(s[i] in big_lat) and (s[i+1] in big_lat) and (s[i]>s[i+1])
			then 
			begin
				ch := s[i];
				s[i] := s[i+1];
				s[i+1] := ch;
				flag := false;
			end;
			inc(z);
	until flag or (z=len);
end;

procedure sort2(var s:string);
var
	i,z,len: word;
	flag: boolean;
	ch:char;
begin
	z := 1;
	len := length(s);
	repeat 
		flag := true;
		for i:=1 to len-z do
			if (pos(s[i],symbtable) > pos(s[i+1], symbtable))
			then 
			begin
				ch := s[i];
				s[i] := s[i+1];
				s[i+1] := ch;
				flag := false;
			end;
			inc(z);
	until flag or (z=len);
end;
end.

