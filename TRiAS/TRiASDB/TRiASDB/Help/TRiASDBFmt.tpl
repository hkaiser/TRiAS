
[extension]
; ADDED: #HK980102
.ext=idl,c

[text]
; ADDED: #HK971228
.tag=tr, both, 0
.format=TRiAS\'ae
.tag=csign, both, 0
.format=\'a9
.tag=rsign, both, 0
.format=\'ae
.tag=tmsign, both, 0
.format=\'99
.tag=nnl, both, 0
.format=\line\line 

; ADDED: version information #HK980103
.tag=copyright, both, 0
.format=@D
.tag=version, both, 0
.format=@A.@B.@C
.tag=company, both, 0
.format=@E

; ADDED: reference to constants: #HK980103
.tag=cv, help, 1
.format={\uldb $1}{\v !Klink($1 constant)}
.if=exists($1)

.tag=cv, both, 1
.format={\b $1}

; ADDED: #HK980219
.tag=b, both, 1
.format={\b $1}

[paragraph]                       
; ADDED: Exceptions: #AK980909
.tag=except, both, 1, 1    
.pre=$(reset)$(rmh)Exception\par
.format=$(reset)$(normal)$1\par
