program lab8;
var D:array [1..10, 1..10] of integer;
  A: array[1..10] of integer;
	i, n, j, sum, mult, sum_all: integer;
	av: real;
	fin, fout: Text;
begin
	assign(fin, 'lab8_in.txt');
	Reset(fin);
	read(fin, n);
	sum_all := 0;
	for i := 1 to n do
  begin
    for j := 1 to n do 
    begin
      read(fin, D[i,j]);
      sum_all := sum_all + D[i,j];
    end;
    readln(fin);
  end;
  sum := 0;
  mult := 1;
  for i := 1 to n do 
  begin
    for j := 1 to n do
    begin
      sum := sum + D[j,i];
      mult := mult * D[j,i];
    end;
    if sum > mult then A[i] := 1 else A[i] := 0;
    sum := 0;
    mult := 1;
  end;
  av := sum_all / (n * n);
  assign(fout, 'lab8_out.txt');
  rewrite(fout);
  writeln(fout, 'from matrix ');
  for i := 1 to n do 
  begin
    for j := 1 to n do 
      write(fout, D[i,j], ' ');
    writeln(fout);
  end;
  write(fout, 'we get massive ');
  for i := 1 to n do 
    write(fout, A[i] , ' ');
  writeln(fout);
  write(fout, 'and avarage is = ', av:0:5);
  close(fout);
  end.
  
      
