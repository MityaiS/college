program Lab5;
  var n, i, k: integer;
  num, min: real;
  A: array[1..10] of real;
  fin, fout: Text;
begin
  assign(fin, 'in_lab5.txt');
  Reset(fin);
  read(fin, n);
  for i:=1 to n do 
    read(fin, A[i]);
  close(fin);
  min := sqr(A[2]) - sqr(A[1]);
  k := 2;
  for i := 3 to n - 2 do 
  begin
    num := sqr(A[i]) - sqr(A[i - 1]);
    if num < min then 
    begin
      min := num;
      k := i;
    end;
  end;
  assign(fout, 'out_lab5.txt');
  Rewrite(fout);
  writeln(fout, k);
  close(fout);
end.
  