#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME PA


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */

/* ---------------------------------------PATHFINDING ALGOS-----------------------------------------*/

//---------DIJKSTRA-----------------------//

const double infinit     = numeric_limits<double>::infinity();

typedef pair<double, int> WArc;
typedef vector<vector<WArc>> WGraph;

void dijkstra(const WGraph& G, int s, vector<double>& d, vector<int>& p) {
    int n = G.size();
    d = vector<double>(n, infinit); d[s] = 0;
    p = vector<int>(n, -1);
    vector<bool> S(n, false);
    priority_queue<WArc, vector<WArc>, greater<WArc> > Q;
    Q.push(WArc(0, s));

    while (not Q.empty()) {
        int u = Q.top().second; Q.pop();
        if (not S[u]) {
            S[u] = true;
            for (WArc a : G[u]) {
            int v = a.second;
            double c = a.first;
                if (d[v] > d[u] + c) {
                    d[v] = d[u] + c;
                    p[v] = u;
                    Q.push(WArc(d[v], v));
                }  
            } 
        }
    }
 }
 
 
 
 //----VERSIO GITHUB ---- 
 
 
 
 
 
 
 
 
 //-----------END --- DIJKSTRA--------------//
















/* ---------------------------------------AUX ALGOS-----------------------------------------*/

//---Position to Graph vertice--
    int postover(Pos p){
        return p.i*60 + p.j;
    }
    
    Pos vertopos(int ver){
		Pos p;
		p.i = ver/60;
		p.j= ver - p.i*60;
		return p;
	}
   

//----Weight of cell p----
    double weight(Pos p){
    		if(p.i < 0 or p.j < 0 or p.i >= 60 or p.j >=60) return infinit;
			CellType t = cell(p).type;
			if(t == Rock){
				cout << "Its a Rock!"<< endl;
				if(cell(p).treasure == 1) return -10;
				else return cell(p).turns;
			}
			else if(t == Granite) return infinit;
			else if(t == Outside) return 0;
			else if(t == Cave){
				if(cell(p).owner != me()) return -1;
				else return 0;
			}
			else if(t == Abyss) return infinit;
			
			return 0;
	}


//--Grid to Graph ----
    WGraph gridtograph(){
        WGraph G(60*60);//
        for(int i= 0; i<60; ++i){
            for(int j=0; j<60; ++j){
            //per cada casella
            //afegeix les del voltant amb els pesos
            	vector<WArc> vert;
            	WArc arc;
            	cout << "--Start-- " << i << ", " << j << endl;
            	
            	for(int l=0; l<8; ++l){
	            	Pos p(i,j);
            		if(l==0) p.i--;
            		else if(l==1){
            			p.i--;
            			p.j++;
            		}
            		else if(l==2) p.j++;
            		else if(l==3){
            			p.i++;
            			p.j++;
            		}
            		else if(l==4) p.i++;
            		else if(l==5){
            			p.i++;
            			p.j--;
            		}
            		else if(l==6) p.j--;
            		else if(l==7){
            			p.i--;
            			p.j--;
            		}
            		
            		if(p.i < 0 or p.j < 0 or p.i >= 60 or p.j >=60){
            			arc.first = infinit;
            			arc.second = -1;
            		}
            		else{
            			
						arc.first=weight(p);
						
						arc.second=postover(p);
            		}
            		Pos pdos(i,j);
					int ver = postover(pdos);
					cout <<"add " << "(" << arc.first << ", " << arc.second << ") to verice:" << ver << endl;
            		G[ver].push_back(arc);
            		
            		cout << "Edge to cell: " << p.i << ", "<< p.j << "Vertice "<< arc.second<<" Weight: " << arc.first << endl;
            		
            	}

				
				cout << "Done i,j: "<< i << ", " << j<< endl;
            }
    	}
    	return G;
    }

//-----Move Dwarve towards d-------

void move_dwarve(int id, int s, int dest, vector<int>& parent){
	int i = dest;
	
	while(parent[i] != s){
		i= parent[i];
	}
	Pos p = vertopos(i);
	int deltax =  p.j - unit(id).pos.j;
	int deltay = p.i - unit(id).pos.i;
	
	Dir d = None;
	if(deltax < 0 and deltay < 0) d = LB;
	else if(deltax < 0 and deltay > 0) d = TL;
	else if(deltax > 0 and deltay < 0) d = BR;
	else if(deltax > 0 and deltay > 0) d = RT;
	
	else if(deltax == 0 and deltay < 0) d = Bottom;
	else if(deltax == 0 and deltay > 0) d = Top;
	else if(deltax > 0 and deltay == 0) d = Right;
	else if(deltax < 0 and deltay == 0) d = Left;
		
	command (id, d);
	
}


//-----Clost tresure----

int cls_treasure(vector<double>& d, int x){
	int min =0;
	int n = d.size();
	for(int i=0; i<n;++i){
		if(d[min]>d[i]) min = i;
	}
	return min;
}

/* ---------------------------------------CELL INFO-----------------------------------------*/









  /**
   * Play method, invoked once per each round.
   */
	virtual void play () {
		cout << "--My Turn---" << endl;
		WGraph G = gridtograph();
		cout << "---Grid To Graph Created---" << endl;
		vector<double> d;
		vector<int> p;
		int x, y;
		
		vector<int> aux =  dwarves(me());
		int n = aux.size();
		cout << "--Dwarves--" << endl;
		for(int i = 0; i<n;++i){
			cout << ", " << aux[a] ;
			cout << endl;
			x = postover(unit(i).pos);
			dijkstra(G, x, d, p);
			y = cls_treasure(d, x);
			move_dwarve(aux[i],x, y, p);
		}
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
