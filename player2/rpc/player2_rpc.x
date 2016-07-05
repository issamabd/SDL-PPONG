/*
 * player2_rpc.x: procedures that will be called remotely by player1
 */

 

program PLAYER2PROG {
        version PLAYER2VERS {
                int LAUNCHBALLP2(void) = 1;
        } = 1;
} = 0x3FFFFFFF;
