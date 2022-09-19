program lab6;
var A:array [1..10] of integer;
	i, n, k1, k2, fmin, x, z: integer;
	fin, fout: Text;
begin
	assign(fin, 'lab6_in.txt');
	Reset(fin);
	read(fin, z);
	read(fin, n);
	k2 := 0;
	for i := 1 to n do 
  begin
		read(fin, A[i]);
		if A[i] mod z = 0 then k2 := i;
	end;
	close(fin);
	k1 := n + 1;
	for i := n downto 1 do
		if A[i] = 0 then k1 := i;
	fmin := A[k2];
	x := k2;
	for i := k2 downto k1 + 1 do
		if A[i] mod z = 0 then
			if A[i] < fmin then begin
				fmin := A[i];
				x := i;
				end;
	assign(fout, 'lab6_out.txt');
	rewrite(fout);
	writeln(fout, x, '- номер нужного эл-та массива', A);
	close(fout);
end.			 	
