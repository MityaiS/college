program Lab5_proc;

type mas = array [1..10] of integer;

Procedure in_mas(fname:string; var A:mas; var n:integer);
var i:integer;
    fin:text;
begin
  assign(fin, fname);
  reset(fin);
  read(fin, n);
  for i := 1 to n do
    read(fin, A[i]);
  close(fin);
end;

Procedure frames(n:integer);
begin
  if (n < 1) or (n > 10) then 
    writeln('Выход за рамки массива 1 < s < 10');
end;

Procedure execution(A:mas; n:integer; var k:integer);
var min, i, num: integer;
begin
  min := sqr(A[2]) - sqr(A[1]);
  k := 2;
  for i := 3 to n  do 
  begin
    num := sqr(A[i]) - sqr(A[i - 1]);
    if num < min then 
    begin
      min := num;
      k := i;
    end;
  end;
end;

Procedure output(A: mas; n:integer; k:integer; fname:string);
var fout:text;
    i: integer;
begin
  assign(fout, fname);
  Rewrite(fout);
  writeln(fout, 'Для массива');
  for i := 1 to n do
    write(fout, A[i] + ' ');
  write(fout, 'Искомым значением является ');
  writeln(fout, k);
  close(fout);
end;
  
    
  
  var n, k: integer;
  A: mas;
begin
  in_mas('lab5_proc_in.txt', A, n);
  frames(n);
  execution(A, n, k);
  output(A, n, k, 'lab5_proc_out.txt');
end.
  