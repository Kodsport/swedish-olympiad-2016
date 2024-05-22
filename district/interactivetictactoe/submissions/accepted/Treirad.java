import java.util.Scanner;
public class Treirad {
  public static void main(String args[]) {
    Scanner sc = new Scanner(System.in);
    String s = sc.next();
    if(s.equals("first")) {
      sc.next();
      sc.next();
      sc.next();
      System.out.println("x..\n...\n...");
    } else {
    }
    while(true) {
      String g = sc.next() + sc.next() + sc.next();
      int deep = 0;
      int[] game = new int[9];
      for(int i = 0; i<9; i++) {
        if(g.charAt(i) == 'x') {
          game[i] = 1;
          deep++;
        } else if(g.charAt(i) == 'o') {
          game[i] = -1;
          deep++;
        } else {
          game[i] = 0;
        }
      }
      if(gamewonnow(game,-1)|| deep == 9) {
        System.exit(0);
      }
      int p = play(game, deep);
      game[p] = 1;
      String out = "";
      for(int i = 0; i<9; i++) {
        if(game[i] == 1) {
          out = out + "x";
        } else if(game[i] == 0) {
          out = out + ".";
        } else {
          out = out + "o";
        }
        if(i%3 == 2) {
          out = out + "\n";
        }
      }
      System.out.print(out);
      System.out.flush();
      if(gamewonnow(game,1) || deep == 8)
        System.exit(0);
    }
    
  }
  public static int p(int [] game, int who, int deep) {
    if(gamewonnow(game,-who))
      return -1;
    if(deep == 9)
      return 0;
    else {
      int min = 1;
      for(int i = 0; i<9; i++) {
        if(game[i] == 0) {
          game[i] = who;
          int sc = p(game,-who,deep+1);
          if(sc<min) 
            min = sc;
          game[i] = 0;
        }
      }
      return -min;
    }
  }
  public static int play(int [] game, int deep) {
    int min = 1;
    int p = 0;
    for(int i = 0; i<9; i++) {
      if(game[i] == 0) {
        game[i] = 1;
        int point = p(game,-1,deep+1);
        if(point<min){
          min = point;
          p = i;
        }
        game[i] = 0;
      }
    }
    
    return p;
  }
  
  public static boolean gamewonnow(int [] game, int who) {
    return  game[0]+game[1]+game[2] == 3*who || 
        game[3]+game[4]+game[5] == 3*who || 
        game[6]+game[7]+game[8] == 3*who || 
        game[0]+game[3]+game[6] == 3*who || 
        game[1]+game[4]+game[7] == 3*who ||
        game[2]+game[5]+game[8] == 3*who ||
        game[0]+game[4]+game[8] == 3*who ||
        game[6]+game[4]+game[2] == 3*who;
  }
}

