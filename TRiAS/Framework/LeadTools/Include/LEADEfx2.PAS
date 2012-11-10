unit Leadefx2;

interface

const
{=========================================================================}
{                       More Constants for ltefx                          }
{=========================================================================}

{Rotate}
  EFX_EFFECT_ROTATE_CLASS                               = 8000;
  EFX_EFFECT_ROTATE_L_TO_R                              = (EFX_EFFECT_ROTATE_CLASS+0);
  EFX_EFFECT_ROTATE_R_TO_L                              = (EFX_EFFECT_ROTATE_CLASS+1);
  EFX_EFFECT_ROTATE_T_TO_B                              = (EFX_EFFECT_ROTATE_CLASS+2);
  EFX_EFFECT_ROTATE_B_TO_T                              = (EFX_EFFECT_ROTATE_CLASS+3);
  EFX_EFFECT_ROTATE4_L_L_L_L                            = (EFX_EFFECT_ROTATE_CLASS+4);
  EFX_EFFECT_ROTATE4_L_L_L_R                            = (EFX_EFFECT_ROTATE_CLASS+5);
  EFX_EFFECT_ROTATE4_L_L_L_T                            = (EFX_EFFECT_ROTATE_CLASS+6);
  EFX_EFFECT_ROTATE4_L_L_L_B                            = (EFX_EFFECT_ROTATE_CLASS+7);
  EFX_EFFECT_ROTATE4_L_L_R_L                            = (EFX_EFFECT_ROTATE_CLASS+8);
  EFX_EFFECT_ROTATE4_L_L_R_R                            = (EFX_EFFECT_ROTATE_CLASS+9);
  EFX_EFFECT_ROTATE4_L_L_R_T                            = (EFX_EFFECT_ROTATE_CLASS+10);
  EFX_EFFECT_ROTATE4_L_L_R_B                            = (EFX_EFFECT_ROTATE_CLASS+11);
  EFX_EFFECT_ROTATE4_L_L_T_L                            = (EFX_EFFECT_ROTATE_CLASS+12);
  EFX_EFFECT_ROTATE4_L_L_T_R                            = (EFX_EFFECT_ROTATE_CLASS+13);
  EFX_EFFECT_ROTATE4_L_L_T_T                            = (EFX_EFFECT_ROTATE_CLASS+14);
  EFX_EFFECT_ROTATE4_L_L_T_B                            = (EFX_EFFECT_ROTATE_CLASS+15);
  EFX_EFFECT_ROTATE4_L_L_B_L                            = (EFX_EFFECT_ROTATE_CLASS+16);
  EFX_EFFECT_ROTATE4_L_L_B_R                            = (EFX_EFFECT_ROTATE_CLASS+17);
  EFX_EFFECT_ROTATE4_L_L_B_T                            = (EFX_EFFECT_ROTATE_CLASS+18);
  EFX_EFFECT_ROTATE4_L_L_B_B                            = (EFX_EFFECT_ROTATE_CLASS+19);
  EFX_EFFECT_ROTATE4_L_R_L_L                            = (EFX_EFFECT_ROTATE_CLASS+20);
  EFX_EFFECT_ROTATE4_L_R_L_R                            = (EFX_EFFECT_ROTATE_CLASS+21);
  EFX_EFFECT_ROTATE4_L_R_L_T                            = (EFX_EFFECT_ROTATE_CLASS+22);
  EFX_EFFECT_ROTATE4_L_R_L_B                            = (EFX_EFFECT_ROTATE_CLASS+23);
  EFX_EFFECT_ROTATE4_L_R_R_L                            = (EFX_EFFECT_ROTATE_CLASS+24);
  EFX_EFFECT_ROTATE4_L_R_R_R                            = (EFX_EFFECT_ROTATE_CLASS+25);
  EFX_EFFECT_ROTATE4_L_R_R_T                            = (EFX_EFFECT_ROTATE_CLASS+26);
  EFX_EFFECT_ROTATE4_L_R_R_B                            = (EFX_EFFECT_ROTATE_CLASS+27);
  EFX_EFFECT_ROTATE4_L_R_T_L                            = (EFX_EFFECT_ROTATE_CLASS+28);
  EFX_EFFECT_ROTATE4_L_R_T_R                            = (EFX_EFFECT_ROTATE_CLASS+29);
  EFX_EFFECT_ROTATE4_L_R_T_T                            = (EFX_EFFECT_ROTATE_CLASS+30);
  EFX_EFFECT_ROTATE4_L_R_T_B                            = (EFX_EFFECT_ROTATE_CLASS+31);
  EFX_EFFECT_ROTATE4_L_R_B_L                            = (EFX_EFFECT_ROTATE_CLASS+32);
  EFX_EFFECT_ROTATE4_L_R_B_R                            = (EFX_EFFECT_ROTATE_CLASS+33);
  EFX_EFFECT_ROTATE4_L_R_B_T                            = (EFX_EFFECT_ROTATE_CLASS+34);
  EFX_EFFECT_ROTATE4_L_R_B_B                            = (EFX_EFFECT_ROTATE_CLASS+35);
  EFX_EFFECT_ROTATE4_L_T_L_L                            = (EFX_EFFECT_ROTATE_CLASS+36);
  EFX_EFFECT_ROTATE4_L_T_L_R                            = (EFX_EFFECT_ROTATE_CLASS+37);
  EFX_EFFECT_ROTATE4_L_T_L_T                            = (EFX_EFFECT_ROTATE_CLASS+38);
  EFX_EFFECT_ROTATE4_L_T_L_B                            = (EFX_EFFECT_ROTATE_CLASS+39);
  EFX_EFFECT_ROTATE4_L_T_R_L                            = (EFX_EFFECT_ROTATE_CLASS+40);
  EFX_EFFECT_ROTATE4_L_T_R_R                            = (EFX_EFFECT_ROTATE_CLASS+41);
  EFX_EFFECT_ROTATE4_L_T_R_T                            = (EFX_EFFECT_ROTATE_CLASS+42);
  EFX_EFFECT_ROTATE4_L_T_R_B                            = (EFX_EFFECT_ROTATE_CLASS+43);
  EFX_EFFECT_ROTATE4_L_T_T_L                            = (EFX_EFFECT_ROTATE_CLASS+44);
  EFX_EFFECT_ROTATE4_L_T_T_R                            = (EFX_EFFECT_ROTATE_CLASS+45);
  EFX_EFFECT_ROTATE4_L_T_T_T                            = (EFX_EFFECT_ROTATE_CLASS+46);
  EFX_EFFECT_ROTATE4_L_T_T_B                            = (EFX_EFFECT_ROTATE_CLASS+47);
  EFX_EFFECT_ROTATE4_L_T_B_L                            = (EFX_EFFECT_ROTATE_CLASS+48);
  EFX_EFFECT_ROTATE4_L_T_B_R                            = (EFX_EFFECT_ROTATE_CLASS+49);
  EFX_EFFECT_ROTATE4_L_T_B_T                            = (EFX_EFFECT_ROTATE_CLASS+50);
  EFX_EFFECT_ROTATE4_L_T_B_B                            = (EFX_EFFECT_ROTATE_CLASS+51);
  EFX_EFFECT_ROTATE4_L_B_L_L                            = (EFX_EFFECT_ROTATE_CLASS+52);
  EFX_EFFECT_ROTATE4_L_B_L_R                            = (EFX_EFFECT_ROTATE_CLASS+53);
  EFX_EFFECT_ROTATE4_L_B_L_T                            = (EFX_EFFECT_ROTATE_CLASS+54);
  EFX_EFFECT_ROTATE4_L_B_L_B                            = (EFX_EFFECT_ROTATE_CLASS+55);
  EFX_EFFECT_ROTATE4_L_B_R_L                            = (EFX_EFFECT_ROTATE_CLASS+56);
  EFX_EFFECT_ROTATE4_L_B_R_R                            = (EFX_EFFECT_ROTATE_CLASS+57);
  EFX_EFFECT_ROTATE4_L_B_R_T                            = (EFX_EFFECT_ROTATE_CLASS+58);
  EFX_EFFECT_ROTATE4_L_B_R_B                            = (EFX_EFFECT_ROTATE_CLASS+59);
  EFX_EFFECT_ROTATE4_L_B_T_L                            = (EFX_EFFECT_ROTATE_CLASS+60);
  EFX_EFFECT_ROTATE4_L_B_T_R                            = (EFX_EFFECT_ROTATE_CLASS+61);
  EFX_EFFECT_ROTATE4_L_B_T_T                            = (EFX_EFFECT_ROTATE_CLASS+62);
  EFX_EFFECT_ROTATE4_L_B_T_B                            = (EFX_EFFECT_ROTATE_CLASS+63);
  EFX_EFFECT_ROTATE4_L_B_B_L                            = (EFX_EFFECT_ROTATE_CLASS+64);
  EFX_EFFECT_ROTATE4_L_B_B_R                            = (EFX_EFFECT_ROTATE_CLASS+65);
  EFX_EFFECT_ROTATE4_L_B_B_T                            = (EFX_EFFECT_ROTATE_CLASS+66);
  EFX_EFFECT_ROTATE4_L_B_B_B                            = (EFX_EFFECT_ROTATE_CLASS+67);
  EFX_EFFECT_ROTATE4_R_L_L_L                            = (EFX_EFFECT_ROTATE_CLASS+68);
  EFX_EFFECT_ROTATE4_R_L_L_R                            = (EFX_EFFECT_ROTATE_CLASS+69);
  EFX_EFFECT_ROTATE4_R_L_L_T                            = (EFX_EFFECT_ROTATE_CLASS+70);
  EFX_EFFECT_ROTATE4_R_L_L_B                            = (EFX_EFFECT_ROTATE_CLASS+71);
  EFX_EFFECT_ROTATE4_R_L_R_L                            = (EFX_EFFECT_ROTATE_CLASS+72);
  EFX_EFFECT_ROTATE4_R_L_R_R                            = (EFX_EFFECT_ROTATE_CLASS+73);
  EFX_EFFECT_ROTATE4_R_L_R_T                            = (EFX_EFFECT_ROTATE_CLASS+74);
  EFX_EFFECT_ROTATE4_R_L_R_B                            = (EFX_EFFECT_ROTATE_CLASS+75);
  EFX_EFFECT_ROTATE4_R_L_T_L                            = (EFX_EFFECT_ROTATE_CLASS+76);
  EFX_EFFECT_ROTATE4_R_L_T_R                            = (EFX_EFFECT_ROTATE_CLASS+77);
  EFX_EFFECT_ROTATE4_R_L_T_T                            = (EFX_EFFECT_ROTATE_CLASS+78);
  EFX_EFFECT_ROTATE4_R_L_T_B                            = (EFX_EFFECT_ROTATE_CLASS+79);
  EFX_EFFECT_ROTATE4_R_L_B_L                            = (EFX_EFFECT_ROTATE_CLASS+80);
  EFX_EFFECT_ROTATE4_R_L_B_R                            = (EFX_EFFECT_ROTATE_CLASS+81);
  EFX_EFFECT_ROTATE4_R_L_B_T                            = (EFX_EFFECT_ROTATE_CLASS+82);
  EFX_EFFECT_ROTATE4_R_L_B_B                            = (EFX_EFFECT_ROTATE_CLASS+83);
  EFX_EFFECT_ROTATE4_R_R_L_L                            = (EFX_EFFECT_ROTATE_CLASS+84);
  EFX_EFFECT_ROTATE4_R_R_L_R                            = (EFX_EFFECT_ROTATE_CLASS+85);
  EFX_EFFECT_ROTATE4_R_R_L_T                            = (EFX_EFFECT_ROTATE_CLASS+86);
  EFX_EFFECT_ROTATE4_R_R_L_B                            = (EFX_EFFECT_ROTATE_CLASS+87);
  EFX_EFFECT_ROTATE4_R_R_R_L                            = (EFX_EFFECT_ROTATE_CLASS+88);
  EFX_EFFECT_ROTATE4_R_R_R_R                            = (EFX_EFFECT_ROTATE_CLASS+89);
  EFX_EFFECT_ROTATE4_R_R_R_T                            = (EFX_EFFECT_ROTATE_CLASS+90);
  EFX_EFFECT_ROTATE4_R_R_R_B                            = (EFX_EFFECT_ROTATE_CLASS+91);
  EFX_EFFECT_ROTATE4_R_R_T_L                            = (EFX_EFFECT_ROTATE_CLASS+92);
  EFX_EFFECT_ROTATE4_R_R_T_R                            = (EFX_EFFECT_ROTATE_CLASS+93);
  EFX_EFFECT_ROTATE4_R_R_T_T                            = (EFX_EFFECT_ROTATE_CLASS+94);
  EFX_EFFECT_ROTATE4_R_R_T_B                            = (EFX_EFFECT_ROTATE_CLASS+95);
  EFX_EFFECT_ROTATE4_R_R_B_L                            = (EFX_EFFECT_ROTATE_CLASS+96);
  EFX_EFFECT_ROTATE4_R_R_B_R                            = (EFX_EFFECT_ROTATE_CLASS+97);
  EFX_EFFECT_ROTATE4_R_R_B_T                            = (EFX_EFFECT_ROTATE_CLASS+98);
  EFX_EFFECT_ROTATE4_R_R_B_B                            = (EFX_EFFECT_ROTATE_CLASS+99);
  EFX_EFFECT_ROTATE4_R_T_L_L                            = (EFX_EFFECT_ROTATE_CLASS+100);
  EFX_EFFECT_ROTATE4_R_T_L_R                            = (EFX_EFFECT_ROTATE_CLASS+101);
  EFX_EFFECT_ROTATE4_R_T_L_T                            = (EFX_EFFECT_ROTATE_CLASS+102);
  EFX_EFFECT_ROTATE4_R_T_L_B                            = (EFX_EFFECT_ROTATE_CLASS+103);
  EFX_EFFECT_ROTATE4_R_T_R_L                            = (EFX_EFFECT_ROTATE_CLASS+104);
  EFX_EFFECT_ROTATE4_R_T_R_R                            = (EFX_EFFECT_ROTATE_CLASS+105);
  EFX_EFFECT_ROTATE4_R_T_R_T                            = (EFX_EFFECT_ROTATE_CLASS+106);
  EFX_EFFECT_ROTATE4_R_T_R_B                            = (EFX_EFFECT_ROTATE_CLASS+107);
  EFX_EFFECT_ROTATE4_R_T_T_L                            = (EFX_EFFECT_ROTATE_CLASS+108);
  EFX_EFFECT_ROTATE4_R_T_T_R                            = (EFX_EFFECT_ROTATE_CLASS+109);
  EFX_EFFECT_ROTATE4_R_T_T_T                            = (EFX_EFFECT_ROTATE_CLASS+110);
  EFX_EFFECT_ROTATE4_R_T_T_B                            = (EFX_EFFECT_ROTATE_CLASS+111);
  EFX_EFFECT_ROTATE4_R_T_B_L                            = (EFX_EFFECT_ROTATE_CLASS+112);
  EFX_EFFECT_ROTATE4_R_T_B_R                            = (EFX_EFFECT_ROTATE_CLASS+113);
  EFX_EFFECT_ROTATE4_R_T_B_T                            = (EFX_EFFECT_ROTATE_CLASS+114);
  EFX_EFFECT_ROTATE4_R_T_B_B                            = (EFX_EFFECT_ROTATE_CLASS+115);
  EFX_EFFECT_ROTATE4_R_B_L_L                            = (EFX_EFFECT_ROTATE_CLASS+116);
  EFX_EFFECT_ROTATE4_R_B_L_R                            = (EFX_EFFECT_ROTATE_CLASS+117);
  EFX_EFFECT_ROTATE4_R_B_L_T                            = (EFX_EFFECT_ROTATE_CLASS+118);
  EFX_EFFECT_ROTATE4_R_B_L_B                            = (EFX_EFFECT_ROTATE_CLASS+119);
  EFX_EFFECT_ROTATE4_R_B_R_L                            = (EFX_EFFECT_ROTATE_CLASS+120);
  EFX_EFFECT_ROTATE4_R_B_R_R                            = (EFX_EFFECT_ROTATE_CLASS+121);
  EFX_EFFECT_ROTATE4_R_B_R_T                            = (EFX_EFFECT_ROTATE_CLASS+122);
  EFX_EFFECT_ROTATE4_R_B_R_B                            = (EFX_EFFECT_ROTATE_CLASS+123);
  EFX_EFFECT_ROTATE4_R_B_T_L                            = (EFX_EFFECT_ROTATE_CLASS+124);
  EFX_EFFECT_ROTATE4_R_B_T_R                            = (EFX_EFFECT_ROTATE_CLASS+125);
  EFX_EFFECT_ROTATE4_R_B_T_T                            = (EFX_EFFECT_ROTATE_CLASS+126);
  EFX_EFFECT_ROTATE4_R_B_T_B                            = (EFX_EFFECT_ROTATE_CLASS+127);
  EFX_EFFECT_ROTATE4_R_B_B_L                            = (EFX_EFFECT_ROTATE_CLASS+128);
  EFX_EFFECT_ROTATE4_R_B_B_R                            = (EFX_EFFECT_ROTATE_CLASS+129);
  EFX_EFFECT_ROTATE4_R_B_B_T                            = (EFX_EFFECT_ROTATE_CLASS+130);
  EFX_EFFECT_ROTATE4_R_B_B_B                            = (EFX_EFFECT_ROTATE_CLASS+131);
  EFX_EFFECT_ROTATE4_T_L_L_L                            = (EFX_EFFECT_ROTATE_CLASS+132);
  EFX_EFFECT_ROTATE4_T_L_L_R                            = (EFX_EFFECT_ROTATE_CLASS+133);
  EFX_EFFECT_ROTATE4_T_L_L_T                            = (EFX_EFFECT_ROTATE_CLASS+134);
  EFX_EFFECT_ROTATE4_T_L_L_B                            = (EFX_EFFECT_ROTATE_CLASS+135);
  EFX_EFFECT_ROTATE4_T_L_R_L                            = (EFX_EFFECT_ROTATE_CLASS+136);
  EFX_EFFECT_ROTATE4_T_L_R_R                            = (EFX_EFFECT_ROTATE_CLASS+137);
  EFX_EFFECT_ROTATE4_T_L_R_T                            = (EFX_EFFECT_ROTATE_CLASS+138);
  EFX_EFFECT_ROTATE4_T_L_R_B                            = (EFX_EFFECT_ROTATE_CLASS+139);
  EFX_EFFECT_ROTATE4_T_L_T_L                            = (EFX_EFFECT_ROTATE_CLASS+140);
  EFX_EFFECT_ROTATE4_T_L_T_R                            = (EFX_EFFECT_ROTATE_CLASS+141);
  EFX_EFFECT_ROTATE4_T_L_T_T                            = (EFX_EFFECT_ROTATE_CLASS+142);
  EFX_EFFECT_ROTATE4_T_L_T_B                            = (EFX_EFFECT_ROTATE_CLASS+143);
  EFX_EFFECT_ROTATE4_T_L_B_L                            = (EFX_EFFECT_ROTATE_CLASS+144);
  EFX_EFFECT_ROTATE4_T_L_B_R                            = (EFX_EFFECT_ROTATE_CLASS+145);
  EFX_EFFECT_ROTATE4_T_L_B_T                            = (EFX_EFFECT_ROTATE_CLASS+146);
  EFX_EFFECT_ROTATE4_T_L_B_B                            = (EFX_EFFECT_ROTATE_CLASS+147);
  EFX_EFFECT_ROTATE4_T_R_L_L                            = (EFX_EFFECT_ROTATE_CLASS+148);
  EFX_EFFECT_ROTATE4_T_R_L_R                            = (EFX_EFFECT_ROTATE_CLASS+149);
  EFX_EFFECT_ROTATE4_T_R_L_T                            = (EFX_EFFECT_ROTATE_CLASS+150);
  EFX_EFFECT_ROTATE4_T_R_L_B                            = (EFX_EFFECT_ROTATE_CLASS+151);
  EFX_EFFECT_ROTATE4_T_R_R_L                            = (EFX_EFFECT_ROTATE_CLASS+152);
  EFX_EFFECT_ROTATE4_T_R_R_R                            = (EFX_EFFECT_ROTATE_CLASS+153);
  EFX_EFFECT_ROTATE4_T_R_R_T                            = (EFX_EFFECT_ROTATE_CLASS+154);
  EFX_EFFECT_ROTATE4_T_R_R_B                            = (EFX_EFFECT_ROTATE_CLASS+155);
  EFX_EFFECT_ROTATE4_T_R_T_L                            = (EFX_EFFECT_ROTATE_CLASS+156);
  EFX_EFFECT_ROTATE4_T_R_T_R                            = (EFX_EFFECT_ROTATE_CLASS+157);
  EFX_EFFECT_ROTATE4_T_R_T_T                            = (EFX_EFFECT_ROTATE_CLASS+158);
  EFX_EFFECT_ROTATE4_T_R_T_B                            = (EFX_EFFECT_ROTATE_CLASS+159);
  EFX_EFFECT_ROTATE4_T_R_B_L                            = (EFX_EFFECT_ROTATE_CLASS+160);
  EFX_EFFECT_ROTATE4_T_R_B_R                            = (EFX_EFFECT_ROTATE_CLASS+161);
  EFX_EFFECT_ROTATE4_T_R_B_T                            = (EFX_EFFECT_ROTATE_CLASS+162);
  EFX_EFFECT_ROTATE4_T_R_B_B                            = (EFX_EFFECT_ROTATE_CLASS+163);
  EFX_EFFECT_ROTATE4_T_T_L_L                            = (EFX_EFFECT_ROTATE_CLASS+164);
  EFX_EFFECT_ROTATE4_T_T_L_R                            = (EFX_EFFECT_ROTATE_CLASS+165);
  EFX_EFFECT_ROTATE4_T_T_L_T                            = (EFX_EFFECT_ROTATE_CLASS+166);
  EFX_EFFECT_ROTATE4_T_T_L_B                            = (EFX_EFFECT_ROTATE_CLASS+167);
  EFX_EFFECT_ROTATE4_T_T_R_L                            = (EFX_EFFECT_ROTATE_CLASS+168);
  EFX_EFFECT_ROTATE4_T_T_R_R                            = (EFX_EFFECT_ROTATE_CLASS+169);
  EFX_EFFECT_ROTATE4_T_T_R_T                            = (EFX_EFFECT_ROTATE_CLASS+170);
  EFX_EFFECT_ROTATE4_T_T_R_B                            = (EFX_EFFECT_ROTATE_CLASS+171);
  EFX_EFFECT_ROTATE4_T_T_T_L                            = (EFX_EFFECT_ROTATE_CLASS+172);
  EFX_EFFECT_ROTATE4_T_T_T_R                            = (EFX_EFFECT_ROTATE_CLASS+173);
  EFX_EFFECT_ROTATE4_T_T_T_T                            = (EFX_EFFECT_ROTATE_CLASS+174);
  EFX_EFFECT_ROTATE4_T_T_T_B                            = (EFX_EFFECT_ROTATE_CLASS+175);
  EFX_EFFECT_ROTATE4_T_T_B_L                            = (EFX_EFFECT_ROTATE_CLASS+176);
  EFX_EFFECT_ROTATE4_T_T_B_R                            = (EFX_EFFECT_ROTATE_CLASS+177);
  EFX_EFFECT_ROTATE4_T_T_B_T                            = (EFX_EFFECT_ROTATE_CLASS+178);
  EFX_EFFECT_ROTATE4_T_T_B_B                            = (EFX_EFFECT_ROTATE_CLASS+179);
  EFX_EFFECT_ROTATE4_T_B_L_L                            = (EFX_EFFECT_ROTATE_CLASS+180);
  EFX_EFFECT_ROTATE4_T_B_L_R                            = (EFX_EFFECT_ROTATE_CLASS+181);
  EFX_EFFECT_ROTATE4_T_B_L_T                            = (EFX_EFFECT_ROTATE_CLASS+182);
  EFX_EFFECT_ROTATE4_T_B_L_B                            = (EFX_EFFECT_ROTATE_CLASS+183);
  EFX_EFFECT_ROTATE4_T_B_R_L                            = (EFX_EFFECT_ROTATE_CLASS+184);
  EFX_EFFECT_ROTATE4_T_B_R_R                            = (EFX_EFFECT_ROTATE_CLASS+185);
  EFX_EFFECT_ROTATE4_T_B_R_T                            = (EFX_EFFECT_ROTATE_CLASS+186);
  EFX_EFFECT_ROTATE4_T_B_R_B                            = (EFX_EFFECT_ROTATE_CLASS+187);
  EFX_EFFECT_ROTATE4_T_B_T_L                            = (EFX_EFFECT_ROTATE_CLASS+188);
  EFX_EFFECT_ROTATE4_T_B_T_R                            = (EFX_EFFECT_ROTATE_CLASS+189);
  EFX_EFFECT_ROTATE4_T_B_T_T                            = (EFX_EFFECT_ROTATE_CLASS+190);
  EFX_EFFECT_ROTATE4_T_B_T_B                            = (EFX_EFFECT_ROTATE_CLASS+191);
  EFX_EFFECT_ROTATE4_T_B_B_L                            = (EFX_EFFECT_ROTATE_CLASS+192);
  EFX_EFFECT_ROTATE4_T_B_B_R                            = (EFX_EFFECT_ROTATE_CLASS+193);
  EFX_EFFECT_ROTATE4_T_B_B_T                            = (EFX_EFFECT_ROTATE_CLASS+194);
  EFX_EFFECT_ROTATE4_T_B_B_B                            = (EFX_EFFECT_ROTATE_CLASS+195);
  EFX_EFFECT_ROTATE4_B_L_L_L                            = (EFX_EFFECT_ROTATE_CLASS+196);
  EFX_EFFECT_ROTATE4_B_L_L_R                            = (EFX_EFFECT_ROTATE_CLASS+197);
  EFX_EFFECT_ROTATE4_B_L_L_T                            = (EFX_EFFECT_ROTATE_CLASS+198);
  EFX_EFFECT_ROTATE4_B_L_L_B                            = (EFX_EFFECT_ROTATE_CLASS+199);
  EFX_EFFECT_ROTATE4_B_L_R_L                            = (EFX_EFFECT_ROTATE_CLASS+200);
  EFX_EFFECT_ROTATE4_B_L_R_R                            = (EFX_EFFECT_ROTATE_CLASS+201);
  EFX_EFFECT_ROTATE4_B_L_R_T                            = (EFX_EFFECT_ROTATE_CLASS+202);
  EFX_EFFECT_ROTATE4_B_L_R_B                            = (EFX_EFFECT_ROTATE_CLASS+203);
  EFX_EFFECT_ROTATE4_B_L_T_L                            = (EFX_EFFECT_ROTATE_CLASS+204);
  EFX_EFFECT_ROTATE4_B_L_T_R                            = (EFX_EFFECT_ROTATE_CLASS+205);
  EFX_EFFECT_ROTATE4_B_L_T_T                            = (EFX_EFFECT_ROTATE_CLASS+206);
  EFX_EFFECT_ROTATE4_B_L_T_B                            = (EFX_EFFECT_ROTATE_CLASS+207);
  EFX_EFFECT_ROTATE4_B_L_B_L                            = (EFX_EFFECT_ROTATE_CLASS+208);
  EFX_EFFECT_ROTATE4_B_L_B_R                            = (EFX_EFFECT_ROTATE_CLASS+209);
  EFX_EFFECT_ROTATE4_B_L_B_T                            = (EFX_EFFECT_ROTATE_CLASS+210);
  EFX_EFFECT_ROTATE4_B_L_B_B                            = (EFX_EFFECT_ROTATE_CLASS+211);
  EFX_EFFECT_ROTATE4_B_R_L_L                            = (EFX_EFFECT_ROTATE_CLASS+212);
  EFX_EFFECT_ROTATE4_B_R_L_R                            = (EFX_EFFECT_ROTATE_CLASS+213);
  EFX_EFFECT_ROTATE4_B_R_L_T                            = (EFX_EFFECT_ROTATE_CLASS+214);
  EFX_EFFECT_ROTATE4_B_R_L_B                            = (EFX_EFFECT_ROTATE_CLASS+215);
  EFX_EFFECT_ROTATE4_B_R_R_L                            = (EFX_EFFECT_ROTATE_CLASS+216);
  EFX_EFFECT_ROTATE4_B_R_R_R                            = (EFX_EFFECT_ROTATE_CLASS+217);
  EFX_EFFECT_ROTATE4_B_R_R_T                            = (EFX_EFFECT_ROTATE_CLASS+218);
  EFX_EFFECT_ROTATE4_B_R_R_B                            = (EFX_EFFECT_ROTATE_CLASS+219);
  EFX_EFFECT_ROTATE4_B_R_T_L                            = (EFX_EFFECT_ROTATE_CLASS+220);
  EFX_EFFECT_ROTATE4_B_R_T_R                            = (EFX_EFFECT_ROTATE_CLASS+221);
  EFX_EFFECT_ROTATE4_B_R_T_T                            = (EFX_EFFECT_ROTATE_CLASS+222);
  EFX_EFFECT_ROTATE4_B_R_T_B                            = (EFX_EFFECT_ROTATE_CLASS+223);
  EFX_EFFECT_ROTATE4_B_R_B_L                            = (EFX_EFFECT_ROTATE_CLASS+224);
  EFX_EFFECT_ROTATE4_B_R_B_R                            = (EFX_EFFECT_ROTATE_CLASS+225);
  EFX_EFFECT_ROTATE4_B_R_B_T                            = (EFX_EFFECT_ROTATE_CLASS+226);
  EFX_EFFECT_ROTATE4_B_R_B_B                            = (EFX_EFFECT_ROTATE_CLASS+227);
  EFX_EFFECT_ROTATE4_B_T_L_L                            = (EFX_EFFECT_ROTATE_CLASS+228);
  EFX_EFFECT_ROTATE4_B_T_L_R                            = (EFX_EFFECT_ROTATE_CLASS+229);
  EFX_EFFECT_ROTATE4_B_T_L_T                            = (EFX_EFFECT_ROTATE_CLASS+230);
  EFX_EFFECT_ROTATE4_B_T_L_B                            = (EFX_EFFECT_ROTATE_CLASS+231);
  EFX_EFFECT_ROTATE4_B_T_R_L                            = (EFX_EFFECT_ROTATE_CLASS+232);
  EFX_EFFECT_ROTATE4_B_T_R_R                            = (EFX_EFFECT_ROTATE_CLASS+233);
  EFX_EFFECT_ROTATE4_B_T_R_T                            = (EFX_EFFECT_ROTATE_CLASS+234);
  EFX_EFFECT_ROTATE4_B_T_R_B                            = (EFX_EFFECT_ROTATE_CLASS+235);
  EFX_EFFECT_ROTATE4_B_T_T_L                            = (EFX_EFFECT_ROTATE_CLASS+236);
  EFX_EFFECT_ROTATE4_B_T_T_R                            = (EFX_EFFECT_ROTATE_CLASS+237);
  EFX_EFFECT_ROTATE4_B_T_T_T                            = (EFX_EFFECT_ROTATE_CLASS+238);
  EFX_EFFECT_ROTATE4_B_T_T_B                            = (EFX_EFFECT_ROTATE_CLASS+239);
  EFX_EFFECT_ROTATE4_B_T_B_L                            = (EFX_EFFECT_ROTATE_CLASS+240);
  EFX_EFFECT_ROTATE4_B_T_B_R                            = (EFX_EFFECT_ROTATE_CLASS+241);
  EFX_EFFECT_ROTATE4_B_T_B_T                            = (EFX_EFFECT_ROTATE_CLASS+242);
  EFX_EFFECT_ROTATE4_B_T_B_B                            = (EFX_EFFECT_ROTATE_CLASS+243);
  EFX_EFFECT_ROTATE4_B_B_L_L                            = (EFX_EFFECT_ROTATE_CLASS+244);
  EFX_EFFECT_ROTATE4_B_B_L_R                            = (EFX_EFFECT_ROTATE_CLASS+245);
  EFX_EFFECT_ROTATE4_B_B_L_T                            = (EFX_EFFECT_ROTATE_CLASS+246);
  EFX_EFFECT_ROTATE4_B_B_L_B                            = (EFX_EFFECT_ROTATE_CLASS+247);
  EFX_EFFECT_ROTATE4_B_B_R_L                            = (EFX_EFFECT_ROTATE_CLASS+248);
  EFX_EFFECT_ROTATE4_B_B_R_R                            = (EFX_EFFECT_ROTATE_CLASS+249);
  EFX_EFFECT_ROTATE4_B_B_R_T                            = (EFX_EFFECT_ROTATE_CLASS+250);
  EFX_EFFECT_ROTATE4_B_B_R_B                            = (EFX_EFFECT_ROTATE_CLASS+251);
  EFX_EFFECT_ROTATE4_B_B_T_L                            = (EFX_EFFECT_ROTATE_CLASS+252);
  EFX_EFFECT_ROTATE4_B_B_T_R                            = (EFX_EFFECT_ROTATE_CLASS+253);
  EFX_EFFECT_ROTATE4_B_B_T_T                            = (EFX_EFFECT_ROTATE_CLASS+254);
  EFX_EFFECT_ROTATE4_B_B_T_B                            = (EFX_EFFECT_ROTATE_CLASS+255);
  EFX_EFFECT_ROTATE4_B_B_B_L                            = (EFX_EFFECT_ROTATE_CLASS+256);
  EFX_EFFECT_ROTATE4_B_B_B_R                            = (EFX_EFFECT_ROTATE_CLASS+257);
  EFX_EFFECT_ROTATE4_B_B_B_T                            = (EFX_EFFECT_ROTATE_CLASS+258);
  EFX_EFFECT_ROTATE4_B_B_B_B                            = (EFX_EFFECT_ROTATE_CLASS+259);
  EFX_EFFECT_ROTATE_MAX                                 = (EFX_EFFECT_ROTATE_CLASS+259);

{Zoom}
  EFX_EFFECT_ZOOM_CLASS                                 = 9000;
  EFX_EFFECT_ZOOM_TO_C                                  = (EFX_EFFECT_ZOOM_CLASS+0);
  EFX_EFFECT_ZOOM_FROM_C                                = (EFX_EFFECT_ZOOM_CLASS+1);
  EFX_EFFECT_ZOOM_MAX                                   = (EFX_EFFECT_ZOOM_CLASS+1);

{Drip}
  EFX_EFFECT_DRIP_CLASS                                 = 10000;
  EFX_EFFECT_DRIP_T_TO_B                                = (EFX_EFFECT_DRIP_CLASS+0);
  EFX_EFFECT_DRIP_B_TO_T                                = (EFX_EFFECT_DRIP_CLASS+1);
  EFX_EFFECT_DRIP_L_TO_R                                = (EFX_EFFECT_DRIP_CLASS+2);
  EFX_EFFECT_DRIP_R_TO_L                                = (EFX_EFFECT_DRIP_CLASS+3);
  EFX_EFFECT_DRIP_MAX                                   = (EFX_EFFECT_DRIP_CLASS+3);

{Blind}
  EFX_EFFECT_BLIND_CLASS                                = 11000;
  EFX_EFFECT_BLIND_T_TO_B                               = (EFX_EFFECT_BLIND_CLASS+0);
  EFX_EFFECT_BLIND_L_TO_R                               = (EFX_EFFECT_BLIND_CLASS+1);
  EFX_EFFECT_BLIND_GROWING_L_TO_R                       = (EFX_EFFECT_BLIND_CLASS+2);
  EFX_EFFECT_BLIND_GROWING_R_TO_L                       = (EFX_EFFECT_BLIND_CLASS+3);
  EFX_EFFECT_BLIND_GROWING_T_TO_B                       = (EFX_EFFECT_BLIND_CLASS+4);
  EFX_EFFECT_BLIND_GROWING_B_TO_T                       = (EFX_EFFECT_BLIND_CLASS+5);
  EFX_EFFECT_BLIND2_T_TO_B_AND_L_TO_R                   = (EFX_EFFECT_BLIND_CLASS+6);
  EFX_EFFECT_BLIND_MAX                                  = (EFX_EFFECT_BLIND_CLASS+6);

{Random}
  EFX_EFFECT_RANDOM_CLASS                               = 12000;
  EFX_EFFECT_RANDOM_BARS_R_TO_L                         = (EFX_EFFECT_RANDOM_CLASS+0);
  EFX_EFFECT_RANDOM_BARS_L_TO_R                         = (EFX_EFFECT_RANDOM_CLASS+1);
  EFX_EFFECT_RANDOM_BARS_B_TO_T                         = (EFX_EFFECT_RANDOM_CLASS+2);
  EFX_EFFECT_RANDOM_BARS_T_TO_B                         = (EFX_EFFECT_RANDOM_CLASS+3);
  EFX_EFFECT_RANDOM_LINES                               = (EFX_EFFECT_RANDOM_CLASS+4);
  EFX_EFFECT_RANDOM_BLOCKS                              = (EFX_EFFECT_RANDOM_CLASS+5);
  EFX_EFFECT_RANDOM_BLOCKS_R_TO_L                       = (EFX_EFFECT_RANDOM_CLASS+6);
  EFX_EFFECT_RANDOM_BLOCKS_L_TO_R                       = (EFX_EFFECT_RANDOM_CLASS+7);
  EFX_EFFECT_RANDOM_BLOCKS_B_TO_T                       = (EFX_EFFECT_RANDOM_CLASS+8);
  EFX_EFFECT_RANDOM_BLOCKS_T_TO_B                       = (EFX_EFFECT_RANDOM_CLASS+9);
  EFX_EFFECT_RANDOM_MAX                                 = (EFX_EFFECT_RANDOM_CLASS+9);

{Checkerboard}
  EFX_EFFECT_CHECKERBOARD_CLASS                         = 13000;
  EFX_EFFECT_CHECKERBOARD_T_TO_B_THEN_T_TO_B            = (EFX_EFFECT_CHECKERBOARD_CLASS+0);
  EFX_EFFECT_CHECKERBOARD_B_TO_T_THEN_B_TO_T            = (EFX_EFFECT_CHECKERBOARD_CLASS+1);
  EFX_EFFECT_CHECKERBOARD_L_TO_R_THEN_L_TO_R            = (EFX_EFFECT_CHECKERBOARD_CLASS+2);
  EFX_EFFECT_CHECKERBOARD_R_TO_L_THEN_R_TO_L            = (EFX_EFFECT_CHECKERBOARD_CLASS+3);
  EFX_EFFECT_CHECKERBOARD_T_TO_B_THEN_B_TO_T            = (EFX_EFFECT_CHECKERBOARD_CLASS+4);
  EFX_EFFECT_CHECKERBOARD_B_TO_T_THEN_T_TO_B            = (EFX_EFFECT_CHECKERBOARD_CLASS+5);
  EFX_EFFECT_CHECKERBOARD_L_TO_R_THEN_R_TO_L            = (EFX_EFFECT_CHECKERBOARD_CLASS+6);
  EFX_EFFECT_CHECKERBOARD_R_TO_L_THEN_L_TO_R            = (EFX_EFFECT_CHECKERBOARD_CLASS+7);
  EFX_EFFECT_CHECKERBOARD_MAX                           = (EFX_EFFECT_CHECKERBOARD_CLASS+7);

{Blocks}
  EFX_EFFECT_BLOCKS_CLASS                               = 14000;
  EFX_EFFECT_BLOCKS_T_TO_B                              = (EFX_EFFECT_BLOCKS_CLASS+0);
  EFX_EFFECT_BLOCKS_B_TO_T                              = (EFX_EFFECT_BLOCKS_CLASS+1);
  EFX_EFFECT_BLOCKS_L_TO_R                              = (EFX_EFFECT_BLOCKS_CLASS+2);
  EFX_EFFECT_BLOCKS_R_TO_L                              = (EFX_EFFECT_BLOCKS_CLASS+3);
  EFX_EFFECT_BLOCKS_SWIRL_CW_TO_C                       = (EFX_EFFECT_BLOCKS_CLASS+4);
  EFX_EFFECT_BLOCKS_SWIRL_CW_FROM_C                     = (EFX_EFFECT_BLOCKS_CLASS+5);
  EFX_EFFECT_BLOCKS_SWIRL_CCW_TO_C                      = (EFX_EFFECT_BLOCKS_CLASS+6);
  EFX_EFFECT_BLOCKS_SWIRL_CCW_FROM_C                    = (EFX_EFFECT_BLOCKS_CLASS+7);
  EFX_EFFECT_BLOCKS_MAX                                 = (EFX_EFFECT_BLOCKS_CLASS+7);

{Circle}
  EFX_EFFECT_CIRCLE_CLASS                               = 15000;
  EFX_EFFECT_CIRCLE_C_IN                                = (EFX_EFFECT_CIRCLE_CLASS+0);
  EFX_EFFECT_CIRCLE_C_OUT                               = (EFX_EFFECT_CIRCLE_CLASS+1);
  EFX_EFFECT_CIRCLE_L_IN                                = (EFX_EFFECT_CIRCLE_CLASS+2);
  EFX_EFFECT_CIRCLE_L_OUT                               = (EFX_EFFECT_CIRCLE_CLASS+3);
  EFX_EFFECT_CIRCLE_R_IN                                = (EFX_EFFECT_CIRCLE_CLASS+4);
  EFX_EFFECT_CIRCLE_R_OUT                               = (EFX_EFFECT_CIRCLE_CLASS+5);
  EFX_EFFECT_CIRCLE_T_IN                                = (EFX_EFFECT_CIRCLE_CLASS+6);
  EFX_EFFECT_CIRCLE_T_OUT                               = (EFX_EFFECT_CIRCLE_CLASS+7);
  EFX_EFFECT_CIRCLE_B_IN                                = (EFX_EFFECT_CIRCLE_CLASS+8);
  EFX_EFFECT_CIRCLE_B_OUT                               = (EFX_EFFECT_CIRCLE_CLASS+9);
  EFX_EFFECT_CIRCLE_C_INTER_IN_THEN_IN                  = (EFX_EFFECT_CIRCLE_CLASS+10);
  EFX_EFFECT_CIRCLE_C_INTER_OUT_THEN_OUT                = (EFX_EFFECT_CIRCLE_CLASS+11);
  EFX_EFFECT_CIRCLE_C_INTER_IN_THEN_OUT                 = (EFX_EFFECT_CIRCLE_CLASS+12);
  EFX_EFFECT_CIRCLE_C_INTER_OUT_THEN_IN                 = (EFX_EFFECT_CIRCLE_CLASS+13);
  EFX_EFFECT_CIRCLE_L_INTER_IN_THEN_IN                  = (EFX_EFFECT_CIRCLE_CLASS+14);
  EFX_EFFECT_CIRCLE_L_INTER_OUT_THEN_OUT                = (EFX_EFFECT_CIRCLE_CLASS+15);
  EFX_EFFECT_CIRCLE_L_INTER_IN_THEN_OUT                 = (EFX_EFFECT_CIRCLE_CLASS+16);
  EFX_EFFECT_CIRCLE_L_INTER_OUT_THEN_IN                 = (EFX_EFFECT_CIRCLE_CLASS+17);
  EFX_EFFECT_CIRCLE_R_INTER_IN_THEN_IN                  = (EFX_EFFECT_CIRCLE_CLASS+18);
  EFX_EFFECT_CIRCLE_R_INTER_OUT_THEN_OUT                = (EFX_EFFECT_CIRCLE_CLASS+19);
  EFX_EFFECT_CIRCLE_R_INTER_IN_THEN_OUT                 = (EFX_EFFECT_CIRCLE_CLASS+20);
  EFX_EFFECT_CIRCLE_R_INTER_OUT_THEN_IN                 = (EFX_EFFECT_CIRCLE_CLASS+21);
  EFX_EFFECT_CIRCLE_T_INTER_IN_THEN_IN                  = (EFX_EFFECT_CIRCLE_CLASS+22);
  EFX_EFFECT_CIRCLE_T_INTER_OUT_THEN_OUT                = (EFX_EFFECT_CIRCLE_CLASS+23);
  EFX_EFFECT_CIRCLE_T_INTER_IN_THEN_OUT                 = (EFX_EFFECT_CIRCLE_CLASS+24);
  EFX_EFFECT_CIRCLE_T_INTER_OUT_THEN_IN                 = (EFX_EFFECT_CIRCLE_CLASS+25);
  EFX_EFFECT_CIRCLE_B_INTER_IN_THEN_IN                  = (EFX_EFFECT_CIRCLE_CLASS+26);
  EFX_EFFECT_CIRCLE_B_INTER_OUT_THEN_OUT                = (EFX_EFFECT_CIRCLE_CLASS+27);
  EFX_EFFECT_CIRCLE_B_INTER_IN_THEN_OUT                 = (EFX_EFFECT_CIRCLE_CLASS+28);
  EFX_EFFECT_CIRCLE_B_INTER_OUT_THEN_IN                 = (EFX_EFFECT_CIRCLE_CLASS+29);
  EFX_EFFECT_CIRCLE_L_R_INTER                           = (EFX_EFFECT_CIRCLE_CLASS+30);
  EFX_EFFECT_CIRCLE_T_B_INTER                           = (EFX_EFFECT_CIRCLE_CLASS+31);
  EFX_EFFECT_CIRCLE2_L_R_OUT                            = (EFX_EFFECT_CIRCLE_CLASS+32);
  EFX_EFFECT_CIRCLE2_L_R_IN                             = (EFX_EFFECT_CIRCLE_CLASS+33);
  EFX_EFFECT_CIRCLE2_T_B_OUT                            = (EFX_EFFECT_CIRCLE_CLASS+34);
  EFX_EFFECT_CIRCLE2_T_B_IN                             = (EFX_EFFECT_CIRCLE_CLASS+35);
  EFX_EFFECT_CIRCLE_MAX                                 = (EFX_EFFECT_CIRCLE_CLASS+35);

{Ellipse}
  EFX_EFFECT_ELLIPSE_CLASS                              = 16000;
  EFX_EFFECT_ELLIPSE_C_IN                               = (EFX_EFFECT_ELLIPSE_CLASS+0);
  EFX_EFFECT_ELLIPSE_C_OUT                              = (EFX_EFFECT_ELLIPSE_CLASS+1);
  EFX_EFFECT_ELLIPSE_L_IN                               = (EFX_EFFECT_ELLIPSE_CLASS+2);
  EFX_EFFECT_ELLIPSE_L_OUT                              = (EFX_EFFECT_ELLIPSE_CLASS+3);
  EFX_EFFECT_ELLIPSE_R_IN                               = (EFX_EFFECT_ELLIPSE_CLASS+4);
  EFX_EFFECT_ELLIPSE_R_OUT                              = (EFX_EFFECT_ELLIPSE_CLASS+5);
  EFX_EFFECT_ELLIPSE_T_IN                               = (EFX_EFFECT_ELLIPSE_CLASS+6);
  EFX_EFFECT_ELLIPSE_T_OUT                              = (EFX_EFFECT_ELLIPSE_CLASS+7);
  EFX_EFFECT_ELLIPSE_B_IN                               = (EFX_EFFECT_ELLIPSE_CLASS+8);
  EFX_EFFECT_ELLIPSE_B_OUT                              = (EFX_EFFECT_ELLIPSE_CLASS+9);
  EFX_EFFECT_ELLIPSE_C_INTER_IN_THEN_IN                 = (EFX_EFFECT_ELLIPSE_CLASS+10);
  EFX_EFFECT_ELLIPSE_C_INTER_OUT_THEN_OUT               = (EFX_EFFECT_ELLIPSE_CLASS+11);
  EFX_EFFECT_ELLIPSE_C_INTER_IN_THEN_OUT                = (EFX_EFFECT_ELLIPSE_CLASS+12);
  EFX_EFFECT_ELLIPSE_C_INTER_OUT_THEN_IN                = (EFX_EFFECT_ELLIPSE_CLASS+13);
  EFX_EFFECT_ELLIPSE_L_INTER_IN_THEN_IN                 = (EFX_EFFECT_ELLIPSE_CLASS+14);
  EFX_EFFECT_ELLIPSE_L_INTER_OUT_THEN_OUT               = (EFX_EFFECT_ELLIPSE_CLASS+15);
  EFX_EFFECT_ELLIPSE_L_INTER_IN_THEN_OUT                = (EFX_EFFECT_ELLIPSE_CLASS+16);
  EFX_EFFECT_ELLIPSE_L_INTER_OUT_THEN_IN                = (EFX_EFFECT_ELLIPSE_CLASS+17);
  EFX_EFFECT_ELLIPSE_R_INTER_IN_THEN_IN                 = (EFX_EFFECT_ELLIPSE_CLASS+18);
  EFX_EFFECT_ELLIPSE_R_INTER_OUT_THEN_OUT               = (EFX_EFFECT_ELLIPSE_CLASS+19);
  EFX_EFFECT_ELLIPSE_R_INTER_IN_THEN_OUT                = (EFX_EFFECT_ELLIPSE_CLASS+20);
  EFX_EFFECT_ELLIPSE_R_INTER_OUT_THEN_IN                = (EFX_EFFECT_ELLIPSE_CLASS+21);
  EFX_EFFECT_ELLIPSE_T_INTER_IN_THEN_IN                 = (EFX_EFFECT_ELLIPSE_CLASS+22);
  EFX_EFFECT_ELLIPSE_T_INTER_OUT_THEN_OUT               = (EFX_EFFECT_ELLIPSE_CLASS+23);
  EFX_EFFECT_ELLIPSE_T_INTER_IN_THEN_OUT                = (EFX_EFFECT_ELLIPSE_CLASS+24);
  EFX_EFFECT_ELLIPSE_T_INTER_OUT_THEN_IN                = (EFX_EFFECT_ELLIPSE_CLASS+25);
  EFX_EFFECT_ELLIPSE_B_INTER_IN_THEN_IN                 = (EFX_EFFECT_ELLIPSE_CLASS+26);
  EFX_EFFECT_ELLIPSE_B_INTER_OUT_THEN_OUT               = (EFX_EFFECT_ELLIPSE_CLASS+27);
  EFX_EFFECT_ELLIPSE_B_INTER_IN_THEN_OUT                = (EFX_EFFECT_ELLIPSE_CLASS+28);
  EFX_EFFECT_ELLIPSE_B_INTER_OUT_THEN_IN                = (EFX_EFFECT_ELLIPSE_CLASS+29);
  EFX_EFFECT_ELLIPSE_L_R_INTER                          = (EFX_EFFECT_ELLIPSE_CLASS+30);
  EFX_EFFECT_ELLIPSE_T_B_INTER                          = (EFX_EFFECT_ELLIPSE_CLASS+31);
  EFX_EFFECT_ELLIPSE2_L_R_OUT                           = (EFX_EFFECT_ELLIPSE_CLASS+32);
  EFX_EFFECT_ELLIPSE2_L_R_IN                            = (EFX_EFFECT_ELLIPSE_CLASS+33);
  EFX_EFFECT_ELLIPSE2_T_B_OUT                           = (EFX_EFFECT_ELLIPSE_CLASS+34);
  EFX_EFFECT_ELLIPSE2_T_B_IN                            = (EFX_EFFECT_ELLIPSE_CLASS+35);
  EFX_EFFECT_ELLIPSE_MAX                                = (EFX_EFFECT_ELLIPSE_CLASS+35);

  EFFECT_RANDOM_PIXEL         = EFX_EFFECT_RANDOM_BLOCKS;                        {close match - use the grain size}
  EFFECT_RANDOM_SMALLBOX      = EFX_EFFECT_RANDOM_BLOCKS;                         {close match - use the grain size}
  EFFECT_RANDOM_MEDIUMBOX     = EFX_EFFECT_RANDOM_BLOCKS;                         {close match - use the grain size}
  EFFECT_RANDOM_LARGEBOX      = EFX_EFFECT_RANDOM_BLOCKS;                         {close match - use the grain size}
  EFFECT_RANDOM_HLINE         = EFX_EFFECT_RANDOM_LINES;                         {close match - use the grain size}
  EFFECT_RANDOM_VLINE         = EFX_EFFECT_RANDOM_LINES;                         {close match - use the grain size}
  EFFECT_HINTERLACE           = EFX_EFFECT_BLIND_T_TO_B;                         {close match}
  EFFECT_VINTERLACE           = EFX_EFFECT_BLIND_L_TO_R;                         {close match}
  EFFECT_SPIRAL_IN            = EFX_EFFECT_BLOCKS_SWIRL_CW_TO_C;
  EFFECT_SPIRAL_OUT           = EFX_EFFECT_BLOCKS_SWIRL_CW_FROM_C;
  EFFECT_VINTERLACE_RIGHT     = EFX_EFFECT_BLIND_T_TO_B;                         {close match}
  EFFECT_VINTERLACE_LEFT      = EFX_EFFECT_BLIND_T_TO_B;                         {close match}
  EFFECT_HINTERLACE_UP        = EFX_EFFECT_BLIND_L_TO_R;                         {close match}
  EFFECT_HINTERLACE_DOWN      = EFX_EFFECT_BLIND_L_TO_R;                         {close match}

{Pattern}
  EFX_PATTERN_CLASS                        = 0;
  EFX_PATTERN_SOLID                        = (EFX_PATTERN_CLASS+0);
  EFX_PATTERN_TRANSPARENT                  = (EFX_PATTERN_CLASS+1);
  EFX_PATTERN_HORZ_LINE                    = (EFX_PATTERN_CLASS+2);
  EFX_PATTERN_VERT_LINE                    = (EFX_PATTERN_CLASS+3);
  EFX_PATTERN_DOWNWARD_DIAG                = (EFX_PATTERN_CLASS+4);
  EFX_PATTERN_UPWARD_DIAG                  = (EFX_PATTERN_CLASS+5);
  EFX_PATTERN_CROSS                        = (EFX_PATTERN_CLASS+6);
  EFX_PATTERN_DIAG_CROSS                   = (EFX_PATTERN_CLASS+7);
  EFX_PATTERN_MAX                          = (EFX_PATTERN_CLASS+7);

{Linear}
  EFX_GRADIENT_LINE_CLASS                  = 1000;
  EFX_GRADIENT_LINE_L_TO_R                 = (EFX_GRADIENT_LINE_CLASS+0);
  EFX_GRADIENT_LINE_R_TO_L                 = (EFX_GRADIENT_LINE_CLASS+1);
  EFX_GRADIENT_LINE_T_TO_B                 = (EFX_GRADIENT_LINE_CLASS+2);
  EFX_GRADIENT_LINE_B_TO_T                 = (EFX_GRADIENT_LINE_CLASS+3);
  EFX_GRADIENT_LINE_LT_TO_RB               = (EFX_GRADIENT_LINE_CLASS+4);
  EFX_GRADIENT_LINE_LB_TO_RT               = (EFX_GRADIENT_LINE_CLASS+5);
  EFX_GRADIENT_LINE_RT_TO_LB               = (EFX_GRADIENT_LINE_CLASS+6);
  EFX_GRADIENT_LINE_RB_TO_LT               = (EFX_GRADIENT_LINE_CLASS+7);
  EFX_GRADIENT_LINE2_L_AND_R_TO_C          = (EFX_GRADIENT_LINE_CLASS+8);
  EFX_GRADIENT_LINE2_C_TO_L_AND_R          = (EFX_GRADIENT_LINE_CLASS+9);
  EFX_GRADIENT_LINE2_T_AND_B_TO_C          = (EFX_GRADIENT_LINE_CLASS+10);
  EFX_GRADIENT_LINE2_C_TO_T_AND_B          = (EFX_GRADIENT_LINE_CLASS+11);
  EFX_GRADIENT_LINE2_LT_AND_RB_TO_C        = (EFX_GRADIENT_LINE_CLASS+12);
  EFX_GRADIENT_LINE2_C_TO_LT_AND_RB        = (EFX_GRADIENT_LINE_CLASS+13);
  EFX_GRADIENT_LINE2_RT_AND_LB_TO_C        = (EFX_GRADIENT_LINE_CLASS+14);
  EFX_GRADIENT_LINE2_C_TO_RT_AND_LB        = (EFX_GRADIENT_LINE_CLASS+15);
  EFX_GRADIENT_LINE_MAX                    = (EFX_GRADIENT_LINE_CLASS+15);

{Angular}
  EFX_GRADIENT_ANGLE_CLASS                 = 2000;
  EFX_GRADIENT_ANGLE_TO_LT                 = (EFX_GRADIENT_ANGLE_CLASS+0);
  EFX_GRADIENT_ANGLE_TO_LB                 = (EFX_GRADIENT_ANGLE_CLASS+1);
  EFX_GRADIENT_ANGLE_TO_RT                 = (EFX_GRADIENT_ANGLE_CLASS+2);
  EFX_GRADIENT_ANGLE_TO_RB                 = (EFX_GRADIENT_ANGLE_CLASS+3);
  EFX_GRADIENT_ANGLE_FROM_LT               = (EFX_GRADIENT_ANGLE_CLASS+4);
  EFX_GRADIENT_ANGLE_FROM_LB               = (EFX_GRADIENT_ANGLE_CLASS+5);
  EFX_GRADIENT_ANGLE_FROM_RT               = (EFX_GRADIENT_ANGLE_CLASS+6);
  EFX_GRADIENT_ANGLE_FROM_RB               = (EFX_GRADIENT_ANGLE_CLASS+7);
  EFX_GRADIENT_ANGLE_MAX                   = (EFX_GRADIENT_ANGLE_CLASS+7);

{Rectangular}
  EFX_GRADIENT_RECTANGLE_CLASS             = 3000;
  EFX_GRADIENT_RECTANGLE_TO_C              = (EFX_GRADIENT_RECTANGLE_CLASS+0);
  EFX_GRADIENT_RECTANGLE_FROM_C            = (EFX_GRADIENT_RECTANGLE_CLASS+1);
  EFX_GRADIENT_RECTANGLE_MAX               = (EFX_GRADIENT_RECTANGLE_CLASS+1);

{Elliptical}
  EFX_GRADIENT_ELLIPSE_CLASS               = 4000;
  EFX_GRADIENT_ELLIPSE_TO_C                = (EFX_GRADIENT_ELLIPSE_CLASS+0);
  EFX_GRADIENT_ELLIPSE_FROM_C              = (EFX_GRADIENT_ELLIPSE_CLASS+1);
  EFX_GRADIENT_ELLIPSE_MAX                 = (EFX_GRADIENT_ELLIPSE_CLASS+1);

{Conical}
  EFX_GRADIENT_CONE_CLASS                  = 5000;
  EFX_GRADIENT_CONE_FROM_L                 = (EFX_GRADIENT_CONE_CLASS+0);
  EFX_GRADIENT_CONE_FROM_R                 = (EFX_GRADIENT_CONE_CLASS+1);
  EFX_GRADIENT_CONE_FROM_T                 = (EFX_GRADIENT_CONE_CLASS+2);
  EFX_GRADIENT_CONE_FROM_B                 = (EFX_GRADIENT_CONE_CLASS+3);
  EFX_GRADIENT_CONE_FROM_LT                = (EFX_GRADIENT_CONE_CLASS+4);
  EFX_GRADIENT_CONE_FROM_LB                = (EFX_GRADIENT_CONE_CLASS+5);
  EFX_GRADIENT_CONE_FROM_RT                = (EFX_GRADIENT_CONE_CLASS+6);
  EFX_GRADIENT_CONE_FROM_RB                = (EFX_GRADIENT_CONE_CLASS+7);
  EFX_GRADIENT_CONE_MAX                    = (EFX_GRADIENT_CONE_CLASS+7);

{Pattern}
  EFX_TRANS_PATTERN_CLASS                  = 0;       
  EFX_TRANS_SOLID                          = (EFX_TRANS_PATTERN_CLASS+0);       
  EFX_TRANS_HORZ_LINE                      = (EFX_TRANS_PATTERN_CLASS+1);   
  EFX_TRANS_VERT_LINE                      = (EFX_TRANS_PATTERN_CLASS+2);   
  EFX_TRANS_DOWNWARD_DIAG                  = (EFX_TRANS_PATTERN_CLASS+3);
  EFX_TRANS_UPWARD_DIAG                    = (EFX_TRANS_PATTERN_CLASS+4);
  EFX_TRANS_CROSS                          = (EFX_TRANS_PATTERN_CLASS+5);   
  EFX_TRANS_DIAG_CROSS                     = (EFX_TRANS_PATTERN_CLASS+6);   
  EFX_TRANS_PATTERN_MAX                    = (EFX_TRANS_PATTERN_CLASS+6);

{Linear gradient}
  EFX_TRANS_GRADIENT_LINE_CLASS            = EFX_GRADIENT_LINE_CLASS;         
  EFX_TRANS_GRADIENT_LINE_L_TO_R           = EFX_GRADIENT_LINE_L_TO_R;         
  EFX_TRANS_GRADIENT_LINE_R_TO_L           = EFX_GRADIENT_LINE_R_TO_L;         
  EFX_TRANS_GRADIENT_LINE_T_TO_B           = EFX_GRADIENT_LINE_T_TO_B;         
  EFX_TRANS_GRADIENT_LINE_B_TO_T           = EFX_GRADIENT_LINE_B_TO_T;         
  EFX_TRANS_GRADIENT_LINE_LT_TO_RB         = EFX_GRADIENT_LINE_LT_TO_RB;       
  EFX_TRANS_GRADIENT_LINE_LB_TO_RT         = EFX_GRADIENT_LINE_LB_TO_RT;       
  EFX_TRANS_GRADIENT_LINE_RT_TO_LB         = EFX_GRADIENT_LINE_RT_TO_LB;       
  EFX_TRANS_GRADIENT_LINE_RB_TO_LT         = EFX_GRADIENT_LINE_RB_TO_LT;       
  EFX_TRANS_GRADIENT_LINE2_L_AND_R_TO_C    = EFX_GRADIENT_LINE2_L_AND_R_TO_C;
  EFX_TRANS_GRADIENT_LINE2_C_TO_L_AND_R    = EFX_GRADIENT_LINE2_C_TO_L_AND_R;  
  EFX_TRANS_GRADIENT_LINE2_T_AND_B_TO_C    = EFX_GRADIENT_LINE2_T_AND_B_TO_C;
  EFX_TRANS_GRADIENT_LINE2_C_TO_T_AND_B    = EFX_GRADIENT_LINE2_C_TO_T_AND_B;  
  EFX_TRANS_GRADIENT_LINE2_LT_AND_RB_TO_C  = EFX_GRADIENT_LINE2_LT_AND_RB_TO_C;
  EFX_TRANS_GRADIENT_LINE2_C_TO_LT_AND_RB  = EFX_GRADIENT_LINE2_C_TO_LT_AND_RB;
  EFX_TRANS_GRADIENT_LINE2_RT_AND_LB_TO_C  = EFX_GRADIENT_LINE2_RT_AND_LB_TO_C;
  EFX_TRANS_GRADIENT_LINE2_C_TO_RT_AND_LB  = EFX_GRADIENT_LINE2_C_TO_RT_AND_LB;
  EFX_TRANS_GRADIENT_LINE_MAX              = EFX_GRADIENT_LINE_MAX;

{Angular gradient}
  EFX_TRANS_GRADIENT_ANGLE_CLASS           = EFX_GRADIENT_ANGLE_CLASS;  
  EFX_TRANS_GRADIENT_ANGLE_TO_LT           = EFX_GRADIENT_ANGLE_TO_LT;  
  EFX_TRANS_GRADIENT_ANGLE_TO_LB           = EFX_GRADIENT_ANGLE_TO_LB;  
  EFX_TRANS_GRADIENT_ANGLE_TO_RT           = EFX_GRADIENT_ANGLE_TO_RT;  
  EFX_TRANS_GRADIENT_ANGLE_TO_RB           = EFX_GRADIENT_ANGLE_TO_RB;  
  EFX_TRANS_GRADIENT_ANGLE_FROM_LT         = EFX_GRADIENT_ANGLE_FROM_LT;
  EFX_TRANS_GRADIENT_ANGLE_FROM_LB         = EFX_GRADIENT_ANGLE_FROM_LB;
  EFX_TRANS_GRADIENT_ANGLE_FROM_RT         = EFX_GRADIENT_ANGLE_FROM_RT;
  EFX_TRANS_GRADIENT_ANGLE_FROM_RB         = EFX_GRADIENT_ANGLE_FROM_RB;
  EFX_TRANS_GRADIENT_ANGLE_MAX             = EFX_GRADIENT_ANGLE_MAX;  

{Rectangular gradient}
  EFX_TRANS_GRADIENT_RECTANGLE_CLASS       = EFX_GRADIENT_RECTANGLE_CLASS;
  EFX_TRANS_GRADIENT_RECTANGLE_TO_C        = EFX_GRADIENT_RECTANGLE_TO_C;
  EFX_TRANS_GRADIENT_RECTANGLE_FROM_C      = EFX_GRADIENT_RECTANGLE_FROM_C;
  EFX_TRANS_GRADIENT_RECTANGLE_MAX         = EFX_GRADIENT_RECTANGLE_MAX;  

{Elliptical gradient}
  EFX_TRANS_GRADIENT_ELLIPSE_CLASS         = EFX_GRADIENT_ELLIPSE_CLASS;  
  EFX_TRANS_GRADIENT_ELLIPSE_TO_C          = EFX_GRADIENT_ELLIPSE_TO_C;  
  EFX_TRANS_GRADIENT_ELLIPSE_FROM_C        = EFX_GRADIENT_ELLIPSE_FROM_C;
  EFX_TRANS_GRADIENT_ELLIPSE_MAX           = EFX_GRADIENT_ELLIPSE_MAX;  

{Conical gradient}
  EFX_TRANS_GRADIENT_CONE_CLASS            = EFX_GRADIENT_CONE_CLASS;
  EFX_TRANS_GRADIENT_CONE_FROM_L           = EFX_GRADIENT_CONE_FROM_L; 
  EFX_TRANS_GRADIENT_CONE_FROM_R           = EFX_GRADIENT_CONE_FROM_R; 
  EFX_TRANS_GRADIENT_CONE_FROM_T           = EFX_GRADIENT_CONE_FROM_T;
  EFX_TRANS_GRADIENT_CONE_FROM_B           = EFX_GRADIENT_CONE_FROM_B; 
  EFX_TRANS_GRADIENT_CONE_FROM_LT          = EFX_GRADIENT_CONE_FROM_LT;
  EFX_TRANS_GRADIENT_CONE_FROM_LB          = EFX_GRADIENT_CONE_FROM_LB;
  EFX_TRANS_GRADIENT_CONE_FROM_RT          = EFX_GRADIENT_CONE_FROM_RT;
  EFX_TRANS_GRADIENT_CONE_FROM_RB          = EFX_GRADIENT_CONE_FROM_RB;
  EFX_TRANS_GRADIENT_CONE_MAX              = EFX_GRADIENT_CONE_MAX; 

  EFX_FRAME_INNER_INSET                  = $0000;
  EFX_FRAME_INNER_RAISED                 = $0001;
  EFX_FRAME_INNER_MASK                   = $000F;
  EFX_FRAME_OUTER_INSET                  = $0000;
  EFX_FRAME_OUTER_RAISED                 = $0010;
  EFX_FRAME_OUTER_MASK                   = $00F0;
  EFX_FRAME_ADJUST_RECT                  = $0100;

  EFX_TEXT_INSETLIGHT                    = $0000;
  EFX_TEXT_INSETHEAVY                    = $0001;
  EFX_TEXT_RAISEDLIGHT                   = $0002;
  EFX_TEXT_RAISEDHEAVY                   = $0003;
  EFX_TEXT_DROPSHADOW                    = $0004;
  EFX_TEXT_BLOCKSHADOW                   = $0005;
  EFX_TEXT_OUTLINEBLOCK                  = $0006;
  EFX_TEXT_INSETEXTRALIGHT               = $0007;
  EFX_TEXT_INSETEXTRAHEAVY               = $0008;
  EFX_TEXT_RAISEDEXTRALIGHT              = $0009;
  EFX_TEXT_RAISEDEXTRAHEAVY              = $000A;
  EFX_TEXT_STYLEMASK                     = $000F;

  EFX_TEXT_LEFT                          = $0000;
  EFX_TEXT_HCENTER                       = $0010;
  EFX_TEXT_RIGHT                         = $0020;
  EFX_TEXT_HMASK                         = $00F0;

  EFX_TEXT_TOP                           = $0000;
  EFX_TEXT_VCENTER                       = $0100;
  EFX_TEXT_BOTTOM                        = $0200;
  EFX_TEXT_VMASK                         = $0F00;

  EFX_TEXT_WORDWRAP                      = $1000;

{Square}
  EFX_SHAPE_SQUARE_CLASS                   = 1000;
  EFX_SHAPE_SQUARE                         = (EFX_SHAPE_SQUARE_CLASS+0);
  EFX_SHAPE_SQUARE_ROUNDED                 = (EFX_SHAPE_SQUARE_CLASS+1);
  EFX_SHAPE_SQUARE_MAX                     = (EFX_SHAPE_SQUARE_CLASS+1);

{Rectangle}
  EFX_SHAPE_RECTANGLE_CLASS                = 2000;
  EFX_SHAPE_RECTANGLE                      = (EFX_SHAPE_RECTANGLE_CLASS+0);
  EFX_SHAPE_RECTANGLE_ROUNDED              = (EFX_SHAPE_RECTANGLE_CLASS+1);
  EFX_SHAPE_RECTANGLE_MAX                  = (EFX_SHAPE_RECTANGLE_CLASS+1);

{Parallelogram}
  EFX_SHAPE_PARALLELOGRAM_CLASS            = 3000;
  EFX_SHAPE_PARALLELOGRAM_L                = (EFX_SHAPE_PARALLELOGRAM_CLASS+0);
  EFX_SHAPE_PARALLELOGRAM_R                = (EFX_SHAPE_PARALLELOGRAM_CLASS+1);
  EFX_SHAPE_PARALLELOGRAM_T                = (EFX_SHAPE_PARALLELOGRAM_CLASS+2);
  EFX_SHAPE_PARALLELOGRAM_B                = (EFX_SHAPE_PARALLELOGRAM_CLASS+3);
  EFX_SHAPE_PARALLELOGRAM_MAX              = (EFX_SHAPE_PARALLELOGRAM_CLASS+3);

{Trapezoid}
  EFX_SHAPE_TRAPEZOID_CLASS                = 4000;
  EFX_SHAPE_TRAPEZOID_L                    = (EFX_SHAPE_TRAPEZOID_CLASS+0);
  EFX_SHAPE_TRAPEZOID_R                    = (EFX_SHAPE_TRAPEZOID_CLASS+1);
  EFX_SHAPE_TRAPEZOID_T                    = (EFX_SHAPE_TRAPEZOID_CLASS+2);
  EFX_SHAPE_TRAPEZOID_B                    = (EFX_SHAPE_TRAPEZOID_CLASS+3);
  EFX_SHAPE_TRAPEZOID_MAX                  = (EFX_SHAPE_TRAPEZOID_CLASS+3);

{Triangle}
  EFX_SHAPE_TRIANGLE_CLASS                 = 5000;
  EFX_SHAPE_TRIANGLE_EQUILATERAL_L         = (EFX_SHAPE_TRIANGLE_CLASS+0);
  EFX_SHAPE_TRIANGLE_EQUILATERAL_R         = (EFX_SHAPE_TRIANGLE_CLASS+1);
  EFX_SHAPE_TRIANGLE_EQUILATERAL_T         = (EFX_SHAPE_TRIANGLE_CLASS+2);
  EFX_SHAPE_TRIANGLE_EQUILATERAL_B         = (EFX_SHAPE_TRIANGLE_CLASS+3);
  EFX_SHAPE_TRIANGLE_ISOSCELES_L           = (EFX_SHAPE_TRIANGLE_CLASS+4);
  EFX_SHAPE_TRIANGLE_ISOSCELES_R           = (EFX_SHAPE_TRIANGLE_CLASS+5);
  EFX_SHAPE_TRIANGLE_ISOSCELES_T           = (EFX_SHAPE_TRIANGLE_CLASS+6);
  EFX_SHAPE_TRIANGLE_ISOSCELES_B           = (EFX_SHAPE_TRIANGLE_CLASS+7);
  EFX_SHAPE_TRIANGLE_RIGHT_LT              = (EFX_SHAPE_TRIANGLE_CLASS+8);
  EFX_SHAPE_TRIANGLE_RIGHT_LB              = (EFX_SHAPE_TRIANGLE_CLASS+9);
  EFX_SHAPE_TRIANGLE_RIGHT_RT              = (EFX_SHAPE_TRIANGLE_CLASS+10);
  EFX_SHAPE_TRIANGLE_RIGHT_RB              = (EFX_SHAPE_TRIANGLE_CLASS+11);
  EFX_SHAPE_TRIANGLE_MAX                   = (EFX_SHAPE_TRIANGLE_CLASS+11);

{Other polygons}
  EFX_SHAPE_OTHER_CLASS                    = 6000;
  EFX_SHAPE_OCTAGON                        = (EFX_SHAPE_OTHER_CLASS+0);
  EFX_SHAPE_DIAMOND                        = (EFX_SHAPE_OTHER_CLASS+1);
  EFX_SHAPE_PENTAGON                       = (EFX_SHAPE_OTHER_CLASS+2);
  EFX_SHAPE_HEXAGON                        = (EFX_SHAPE_OTHER_CLASS+3);
  EFX_SHAPE_LINE                           = (EFX_SHAPE_OTHER_CLASS+4);
  EFX_SHAPE_REGION                         = (EFX_SHAPE_OTHER_CLASS+5);
  EFX_SHAPE_OTHER_MAX                      = (EFX_SHAPE_OTHER_CLASS+5);

{Circle}
  EFX_SHAPE_CIRCLE_CLASS                   = 7000;
  EFX_SHAPE_CIRCLE                         = (EFX_SHAPE_CIRCLE_CLASS+0);
  EFX_SHAPE_CIRCLE_90_LT                   = (EFX_SHAPE_CIRCLE_CLASS+1);
  EFX_SHAPE_CIRCLE_90_LB                   = (EFX_SHAPE_CIRCLE_CLASS+2);
  EFX_SHAPE_CIRCLE_90_RT                   = (EFX_SHAPE_CIRCLE_CLASS+3);
  EFX_SHAPE_CIRCLE_90_RB                   = (EFX_SHAPE_CIRCLE_CLASS+4);
  EFX_SHAPE_CIRCLE_180_L                   = (EFX_SHAPE_CIRCLE_CLASS+5);
  EFX_SHAPE_CIRCLE_180_R                   = (EFX_SHAPE_CIRCLE_CLASS+6);
  EFX_SHAPE_CIRCLE_180_T                   = (EFX_SHAPE_CIRCLE_CLASS+7);
  EFX_SHAPE_CIRCLE_180_B                   = (EFX_SHAPE_CIRCLE_CLASS+8);
  EFX_SHAPE_CIRCLE_270_LT                  = (EFX_SHAPE_CIRCLE_CLASS+9);
  EFX_SHAPE_CIRCLE_270_LB                  = (EFX_SHAPE_CIRCLE_CLASS+10);
  EFX_SHAPE_CIRCLE_270_RT                  = (EFX_SHAPE_CIRCLE_CLASS+11);
  EFX_SHAPE_CIRCLE_270_RB                  = (EFX_SHAPE_CIRCLE_CLASS+12);
  EFX_SHAPE_CIRCLE_MAX                     = (EFX_SHAPE_CIRCLE_CLASS+12);

{Ellipse}
  EFX_SHAPE_ELLIPSE_CLASS                  = 8000;
  EFX_SHAPE_ELLIPSE                        = (EFX_SHAPE_ELLIPSE_CLASS+0);
  EFX_SHAPE_ELLIPSE_90_LT                  = (EFX_SHAPE_ELLIPSE_CLASS+1);
  EFX_SHAPE_ELLIPSE_90_LB                  = (EFX_SHAPE_ELLIPSE_CLASS+2);
  EFX_SHAPE_ELLIPSE_90_RT                  = (EFX_SHAPE_ELLIPSE_CLASS+3);
  EFX_SHAPE_ELLIPSE_90_RB                  = (EFX_SHAPE_ELLIPSE_CLASS+4);
  EFX_SHAPE_ELLIPSE_180_L                  = (EFX_SHAPE_ELLIPSE_CLASS+5);
  EFX_SHAPE_ELLIPSE_180_R                  = (EFX_SHAPE_ELLIPSE_CLASS+6);
  EFX_SHAPE_ELLIPSE_180_T                  = (EFX_SHAPE_ELLIPSE_CLASS+7);
  EFX_SHAPE_ELLIPSE_180_B                  = (EFX_SHAPE_ELLIPSE_CLASS+8);
  EFX_SHAPE_ELLIPSE_270_LT                 = (EFX_SHAPE_ELLIPSE_CLASS+9);
  EFX_SHAPE_ELLIPSE_270_LB                 = (EFX_SHAPE_ELLIPSE_CLASS+10);
  EFX_SHAPE_ELLIPSE_270_RT                 = (EFX_SHAPE_ELLIPSE_CLASS+11);
  EFX_SHAPE_ELLIPSE_270_RB                 = (EFX_SHAPE_ELLIPSE_CLASS+12);
  EFX_SHAPE_ELLIPSE_MAX                    = (EFX_SHAPE_ELLIPSE_CLASS+12);

{Star}
  EFX_SHAPE_STAR_CLASS                     = 9000;
  EFX_SHAPE_STAR4                          = (EFX_SHAPE_STAR_CLASS+0);
  EFX_SHAPE_STAR5                          = (EFX_SHAPE_STAR_CLASS+1);
  EFX_SHAPE_STAR8                          = (EFX_SHAPE_STAR_CLASS+2);
  EFX_SHAPE_STAR16                         = (EFX_SHAPE_STAR_CLASS+3);
  EFX_SHAPE_STAR24                         = (EFX_SHAPE_STAR_CLASS+4);
  EFX_SHAPE_STAR32                         = (EFX_SHAPE_STAR_CLASS+5);
  EFX_SHAPE_STAR_MAX                       = (EFX_SHAPE_STAR_CLASS+5);

{Coss}
  EFX_SHAPE_CROSS_CLASS                    = 10000;
  EFX_SHAPE_CROSS_SMALL                    = (EFX_SHAPE_CROSS_CLASS+0);
  EFX_SHAPE_CROSS_MEDIUM                   = (EFX_SHAPE_CROSS_CLASS+1);
  EFX_SHAPE_CROSS_LARGE                    = (EFX_SHAPE_CROSS_CLASS+2);
  EFX_SHAPE_CROSS_MAX                      = (EFX_SHAPE_CROSS_CLASS+2);

{Arrow}
  EFX_SHAPE_ARROW_CLASS                    = 11000;
  EFX_SHAPE_ARROW_L                        = (EFX_SHAPE_ARROW_CLASS+0);
  EFX_SHAPE_ARROW_R                        = (EFX_SHAPE_ARROW_CLASS+1);
  EFX_SHAPE_ARROW_T                        = (EFX_SHAPE_ARROW_CLASS+2);
  EFX_SHAPE_ARROW_B                        = (EFX_SHAPE_ARROW_CLASS+3);
  EFX_SHAPE_ARROW2_L_AND_R                 = (EFX_SHAPE_ARROW_CLASS+4);
  EFX_SHAPE_ARROW2_T_AND_B                 = (EFX_SHAPE_ARROW_CLASS+5);
  EFX_SHAPE_ARROW2_L_AND_T                 = (EFX_SHAPE_ARROW_CLASS+6);
  EFX_SHAPE_ARROW2_L_AND_B                 = (EFX_SHAPE_ARROW_CLASS+7);
  EFX_SHAPE_ARROW2_R_AND_T                 = (EFX_SHAPE_ARROW_CLASS+8);
  EFX_SHAPE_ARROW2_R_AND_B                 = (EFX_SHAPE_ARROW_CLASS+9);
  EFX_SHAPE_ARROW3_L_AND_T_AND_R           = (EFX_SHAPE_ARROW_CLASS+10);
  EFX_SHAPE_ARROW3_T_AND_R_AND_B           = (EFX_SHAPE_ARROW_CLASS+11);
  EFX_SHAPE_ARROW3_L_AND_B_AND_R           = (EFX_SHAPE_ARROW_CLASS+12);
  EFX_SHAPE_ARROW3_L_AND_T_AND_B           = (EFX_SHAPE_ARROW_CLASS+13);
  EFX_SHAPE_ARROW4_L_AND_T_AND_R_AND_B     = (EFX_SHAPE_ARROW_CLASS+14);
  EFX_SHAPE_ARROW_MAX                      = (EFX_SHAPE_ARROW_CLASS+14);

  EFX_BORDERSTYLE_TRANSPARENT            = 0;
  EFX_BORDERSTYLE_SOLID                  = 1;
  EFX_BORDERSTYLE_DASH                   = 2;
  EFX_BORDERSTYLE_DOT                    = 3;
  EFX_BORDERSTYLE_DASHDOT                = 4;
  EFX_BORDERSTYLE_DASHDOTDOT             = 5;

  EFX_FILLSTYLE_SOLID                    = 0;
  EFX_FILLSTYLE_TRANSPARENT              = 1;
  EFX_FILLSTYLE_HORIZONTAL               = 2;
  EFX_FILLSTYLE_VERTICAL                 = 3;
  EFX_FILLSTYLE_FDIAGONAL                = 4;
  EFX_FILLSTYLE_BDIAGONAL                = 5;
  EFX_FILLSTYLE_CROSS                    = 6;
  EFX_FILLSTYLE_DIAGCROSS                = 7;

  EFX_BACKSTYLE_TRANSPARENT              = 0;
  EFX_BACKSTYLE_OPAQUE                   = 1;
  EFX_BACKSTYLE_TRANSLUCENT              = 2;
  EFX_BACKSTYLE_TILEDIMAGE               = 3;
  EFX_BACKSTYLE_TRANSLUCENTTILEDIMAGE    = 4;

  EFX_INNERSTYLE_NONE                    = 0;
  EFX_INNERSTYLE_INSET                   = 1;
  EFX_INNERSTYLE_RAISED                  = 3;

  EFX_OUTERSTYLE_NONE                    = 0;
  EFX_OUTERSTYLE_INSET                   = 1;
  EFX_OUTERSTYLE_RAISED                  = 2;

implementation

end.
