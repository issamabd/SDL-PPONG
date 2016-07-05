/*
 * player2_rpc.x: procedures that will be called remotely by player1
 */

 

program PLAYER1PROG {
        version PLAYER1VERS {
                int LAUNCHBALLP1(void) = 1;
                int GETRACK1(int) = 2;
        } = 1;
} = 0x3FFFFFFE;
