
Unit UnVar;
{$MODE DELPHI}

Interface

Uses UnList;

Var NachaloSpiska, KonecSpiska: PElem;

Implementation

initialization
NachaloSpiska := Nil;
KonecSpiska := Nil;
finalization
FreeList(NachaloSpiska, KonecSpiska);
End.
