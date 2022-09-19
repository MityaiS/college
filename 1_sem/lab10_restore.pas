program lab10;

const n = 10;

type mas = array [1..n] of integer;

procedure in_mas(fname:string; var x:mas);
var i:integer;
    fin:text;
begin 
  assign(fin, fname);
  reset(fin);
  readln(fin);
  for i := 1 to n do 
    read(fin, x[i]);
  close(fin);
end;

function in_z(fname:string):integer;
var fin:text;
    x: integer;
begin
  assign(fin, fname);
  reset(fin);
  read(fin, x);
  in_z := x;
end;

function num_of_first_zero(A:mas):integer;
var i, x:integer;
begin
  x := n + 1;
  for i := n downto 1 do 
    if A[i] = 0 then x := i;
  num_of_first_zero := x
end;

function finally_find_what_we_needO_o(A:mas; f_z, z:integer):integer;
var i, x, xmin:integer;
begin
  x := n;
  xmin := A[n];
  for i := n downto f_z + 1 do 
    if (A[i] mod z = 0) and (A[i] <> 0) and (A[i] <= xmin) then
    begin
      xmin := A[i];
      x := i;
    end;
  finally_find_what_we_needO_o := x;
end;

procedure output(A:mas; x:integer; fname:string);
var i:integer;
    fout:text;
begin
  assign(fout, fname);
  rewrite(fout);
  write(fout, 'Для массива ');
  for i := 1 to n do
    write(fout, A[i], ' ');
  write(fout, 'искомое число есть ', x);
  close(fout);
    
end;

var A:mas;
	  f_z, x, z: integer;
begin
  z := in_z('lab10_in.txt');
	in_mas('lab10_in.txt', A);
	f_z := num_of_first_zero(A);
	x := finally_find_what_we_needO_o(A, f_z, z);
	output(A, x, 'lab10_out.txt')
	
end.