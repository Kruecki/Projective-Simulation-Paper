#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char **argv){
  int attacker, defender, reward, symbol, marginal;
  double random, transitionProb[4][2], dissipation, data[501], weight[4][2];
  
  for (int i = 0; i <= 500; i++){
    data[i] = 0;
  }
  
  dissipation = atof(argv[1]);
  
  srand(time(NULL));
  
  for (int realisation = 0; realisation < 1000; realisation++){
    weight[0][0] = 1;
    weight[0][1] = 1;
    weight[1][0] = 1;
    weight[1][1] = 1;
    weight[2][0] = 1;
    weight[2][1] = 1;
    weight[3][0] = 1;
    weight[3][1] = 1;
    for (int cycle = 1; cycle <= 200; cycle++){
      
      // transition probabilities
      for (int nPercept = 0; nPercept < 4; nPercept++){
        marginal = 0;
        for (int nAction = 0; nAction < 2; nAction++){
          marginal += weight[nPercept][nAction];
        }
        for (int nAction = 0; nAction < 2; nAction++){
          transitionProb[nPercept][nAction] = static_cast <double> (weight[nPercept][nAction]) / static_cast <double> (marginal);
        }
      }
      
      // game
      attacker = rand()%2;
      random = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

      if (random < transitionProb[attacker][1]){
        defender = 1;
      }else{
        defender = 0;
      }
      
      if (defender == attacker){
        weight[attacker][attacker]++;
        data[cycle] += 1; // counting successful defence for each timestep (cycle)
      }
      
      // dissipation
      for (int nPercept = 0; nPercept < 4; nPercept++){
        for (int nAction = 0; nAction < 2; nAction++){
          weight[nPercept][nAction] += -dissipation * (weight[nPercept][nAction] - 1);
        }
      }
    }

    // new colour
    for (int cycle = 201; cycle <= 400; cycle++){
      
      // transition probabilities
      for (int nPercept = 0; nPercept < 4; nPercept++){
        marginal = 0;
        for (int nAction = 0; nAction < 2; nAction++){
          marginal += weight[nPercept][nAction];
        }
        for (int nAction = 0; nAction < 2; nAction++){
          transitionProb[nPercept][nAction] = static_cast <double> (weight[nPercept][nAction]) / static_cast <double> (marginal);
        }
      }
      
      // game
      // new color represented by numbers 2 and 3 instead 0 and 1
      attacker = rand()%2 + 2;
      random = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

      if (random < transitionProb[attacker][1]){
        defender = 1;
      }else{
        defender = 0;
      }
      
      if (defender == attacker - 2){
        weight[attacker][defender]++;
        data[cycle] += 1;
      }
      
      // dissipation
      for (int nPercept = 0; nPercept < 4; nPercept++){
        for (int nAction = 0; nAction < 2; nAction++){
          weight[nPercept][nAction] += -dissipation * (weight[nPercept][nAction] - 1);
        }
      }
    }
  }
  
  // save to file
  fstream output;
  output.open("dataFig6.dat", fstream::out);
  for (int i = 1; i <= 400; i++){
    //cout << to_string (data[i]) << endl;
    output << data[i] << endl;
  }
  output.close();

  //delete [] data;

  return 0;
}

