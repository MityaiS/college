program lab11;

const n = 5;

type mas = array [1..n] of integer;
    mat = array [1..n, 1..n] of integer;

function in_mat(fname:string):mat;
var i, j:integer;
    fin:text;
    x:mat;
begin 
  assign(fin, fname);
  reset(fin);
  for i := 1 to n do
  begin
    for j := 1 to n do 
      read(fin, x[i,j]); 
    readln(fin);
  end;
  close(fin);
  in_mat := x;
end;

procedure creating_mas_and_finding_av_of_all_in_this_matrix_so_we_could_do_our_business(D:mat; var x:mas;var av:real);
var i, j, sum, mult, sum_all:integer;
begin
  for i := 1 to n do 
  begin
    sum := 0;
    mult := 1;
    for j := 1 to n do 
    begin
      sum += D[j,i];
      mult *= D[j,i];
    end;
    if sum > mult then x[i] := 1 else x[i] := 0;
    sum_all += sum;
  end;
  av := sum_all/(n*n);
end;


procedure output(X:mat; av:real; fname:string; M:mas);
var fin: text;
    i, j:integer;
begin
  assign(fin, fname);
  rewrite(fin);
  write(fin, 'Для матрицы ');
  writeln(fin);
  for i := 1 to n do 
    begin
    for j := 1 to n do
      write(fin, x[i,j] + ' ');
    writeln(fin);
    end;
  write(fin, 'среднее арифметическое = ');
  writeln(fin, av);
  writeln(fin, 'А массив ');
  for i := 1 to n do 
    write(fin, M[i] + ' ');
  close(fin);
end;

function minimum_av(av1,av2, av3:real):real;
var min_av:real;
begin
  if av1 < av2 then min_av := av1 else min_av := av2;
  if av3 < min_av then min_av := av3;
  minimum_av := min_av;
end;

procedure another_output(min_av:real; fname:string);
var fin:text;
begin
  assign(fin,fname);
  rewrite(fin);
  write(fin, 'Наименьшое среднее ');
  write(fin, min_av);
  close(fin);
end;


var a, b, c: mat;
    am, bm, cm :mas;
    aav, bav, cav, min_av: real;
begin
  a := in_mat('lab11_in_a.txt');
  b := in_mat('lab11_in_b.txt');
  c := in_mat('lab11_in_c.txt');
  creating_mas_and_finding_av_of_all_in_this_matrix_so_we_could_do_our_business(a, am, aav);
  creating_mas_and_finding_av_of_all_in_this_matrix_so_we_could_do_our_business(b, bm, bav);
  creating_mas_and_finding_av_of_all_in_this_matrix_so_we_could_do_our_business(c, cm, cav);
  output(a, aav, 'lab11_out_a.txt', am);
  output(b, bav, 'lab11_out_b.txt', bm);
  output(c, cav, 'lab11_out_c.txt', cm);
  min_av := minimum_av(aav, bav, cav);
  another_output(min_av, 'lab11_out_final.txt')
end.