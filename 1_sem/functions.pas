unit functions;

Interface 
const n = 5;

type mas = array [1..n] of integer;
    mat = array [1..n, 1..n] of integer;
    

procedure if_wrong(m:integer);
procedure in_mat(fname:string; var X:mat; var m:integer);
function in_mas(fname:string; m:integer):mas;
function is_everything_right(B:mat; C:mas; m:integer):boolean;
function replacement(B:mat; m:integer):mas;
procedure output(Right:boolean; B:mat; C:mas; fname:string; D:mas; m:integer);

implementation
procedure if_wrong;
begin
  if m > n then write('Слишком большой m');
end;

procedure in_mat;
var i, j:integer;
    fin:text;
begin 
  assign(fin, fname);
  reset(fin);
  read(fin, m);
  if_wrong(m);
  for i := 1 to m do
  begin
    for j := 1 to m do 
      read(fin, x[i,j]); 
    readln(fin);
  end;
  close(fin);
end;

function in_mas:mas;
var i:integer;
    fin:text;
    x:mas;
begin
  assign(fin, fname);
  reset(fin);
  for i := 1 to m do
    read(fin, x[i]);
  close(fin);
  in_mas := x;
end;

function is_everything_right:boolean;
var i,j:integer;
    Right:boolean;
begin
  Right := True;
  for i := 1 to m do 
    if right then
      for j := 1 to m do
        if B[i,j] >= C[i] then Right := False;
  is_everything_right := Right;
end;

function replacement:mas;
var i,j:integer;
    min:integer;
    X:mas;
begin
  for i := 1 to m do
  begin
    min := B[i,1];
    for j := 1 to m do 
      if min > B[i,j] then min := B[i,j];
    X[i] := min;
  end;
  replacement := X;
end;

procedure output;
var i,j:integer;
    fin: text;
begin
  assign(fin, fname);
  rewrite(fin);
  writeln(fin, 'Для матрицы');
  for i := 1 to m do 
  begin 
    for j := 1 to m do
      write(fin, B[i,j] + ' ');
    writeln(fin);
  end;
  writeln(fin, 'И массива ');
  for i := 1 to m do
    write(fin, C[i] + ' ');
  if right then
  begin
    write(fin, 'решением будет массив ');
    for i := 1 to m do 
      write(fin, D[i] + ' ');
  end
  else write(fin, 'решений нет');
  close(fin);
end;

end.
