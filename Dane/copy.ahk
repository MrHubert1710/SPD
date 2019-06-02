#CommentFlag //
Sniper(rep)
{   
        CoordMode, ToolTip, screen
        CoordMode, Mouse, screen
        CoordMode, Pixel, screen
        SysGet, VirtualScreenWidth, 78
        SysGet, VirtualScreenHeight, 79

        SysGet, VirtualScreenLeft, 76
        SysGet, VirtualScreenTop, 77
        demoX:=1975
        demoY:=473
        next_demoX:=2000
        next_demoY:=475
        txt1_demoX:=2044
        txt1_demoY:=100
        txt2_demoX:=2664
        txt2_demoY:=455
        dstX:=30
        dstY:=186
        next_dstX:=130
        next_dstY:=186
        MouseMove, WhispX, WhispY
        MouseClick, left, WhispX, WhispY
        Send, ^f
        
        
        Skrypt:
        Loop
        {
            
            MouseMove, demoX, demoY,5
            Sleep, 100
            MouseClick, left, demoX, demoY
            
            Sleep, 10
            
            MouseMove, txt1_demoX, txt1_demoY, 5
            Sleep, 100
            MouseClick, left, txt1_demoX, txt1_demoY
            
            Send, {LShift Down}
            
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            Sleep, 1
            Send, {PgDn Down}
            Sleep, 2
            Send, {PgDn Up}
            
            MouseMove, txt2_demoX, txt2_demoY, 5
            Sleep, 100
            MouseClick, left, txt2_demoX, txt2_demoY
            
            Send, {Down Down}
            Sleep, 10
            Send, {Down Up}
            Send, {LShift Up}
            
            Send, ^c
            
            MouseClick, left, dstX, dstY
            Send, ^v
            Send, ^s
            MouseClick, left, next_dstX, next_dstY
            MouseClick, left, next_demoX, next_demoY
            Sleep, 500
        
        
            if(rep>=1){
                if(rep==1)
                    break, Skrypt
                else
                    rep:=rep-1
            }
        }
}

+b::
Sniper(121)
Return

Esc::ExitApp