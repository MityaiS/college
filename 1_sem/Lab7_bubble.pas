program Lab5;
  var n, i, j, k: integer;
  A: array[1..10] of integer;
  fin, fout: Text;
begin
  assign(fin, 'in_lab7.txt');
  Reset(fin);
  read(fin, n);
  for i:=1 to n do 
    read(fin, A[i]);
  close(fin);
  assign(fout, 'out_lab7.txt');
  Rewrite(fout);
  for i:=1 to n-1 do begin
    for j:=1 to n-i do begin
      if A[j]>A[j+1] then begin
        k:=A[j];
        A[j]:=A[j+1];
        A[j+1]:=k;
      end;
    end;
    for j:= 1 to n do
      write(fout, A[j]+' ');
    writeln(fout);
  end;

  for i:= 1 to n do
    write(fout, A[i]+' ');
  close(fout);
end.
  