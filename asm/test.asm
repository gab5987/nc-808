; Test code for nc-808
; Basically how the sintax will work

; This is a comment
# Comments are also allowed with the # symbol

@macro: test_macro ld 0x00, 0x00 ; this is how a macro will look like

; macros are defined with the @macro keyword
; multiline macros are (still) not allowed because it wouldnt make any sense(thats why the methods exists)

$myVar 0x00 ; this is how a variable will look like

; Variables are global by default, its value will acctually be pointing... 
; ...to the memory address of the variable, so you can use it as a pointer too


; methods are defined with the "def:" keyword, and end with the "end" keyword
def: someMethod    ; this is how a method will look like
    nop
    add
    @test_macro    ; you can also use the @ symbol to call a macro (macros are defined with the @macro sintax)
    ld 0x01 0x10
    out 0x01 0x10 
end                ; methods must end with the "end" keyword

; the main method is defined with the "main:" keyword, and end with the "end" keyword
main:              ; this is how the main method will look like
    in 0x3f
    call someMethod ; this is how a method call will look like
end ; at the end of the main method, the compiler will automatically add a HALT instruction

; THINGS TO CONSIDER WHEN WRITING CODE
; - the compiler will automatically add a JMP instruction at the beggining of the code to jump to the main method.
; - the compiler will automatically add a HALT instruction at the end of the main method.
; - variables are always stored at the beggining of the memory, to acces it you must use a LDI instruction.

;    AND THATS ALL FOLKS!
