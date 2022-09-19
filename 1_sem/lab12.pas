

program lab12;

uses functions in 'functions.pas';

var b:mat;
    c, d:mas;
    right:boolean;
    m:integer;
begin
  in_mat('lab12_in_mat.txt', B, m);
  C := in_mas('lab12_in_mas.txt', m);
  Right := is_everything_right(B, C, m);
  if right then D := replacement(B, m);
  output(Right, B, C, 'lab12_out.txt', D, m);
end.
  
      
      