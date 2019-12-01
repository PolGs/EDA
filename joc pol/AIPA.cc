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
			CellType t = cell(p).type;
    		if(p.i < 0 or p.j < 0 or p.i >= 60 or p.j >=60) return infinit;
			else if(t == Rock) return random(1000,800);
			else if(t == Granite) return infinit;
			else if(t == Outside) return random(800,700);
			else if(t == Cave){
				if(cell(p).treasure) return 0;
				else if(cell(p).owner != me()) return random(400,300);
				else return random(1000,800);
			}
			else if(t == Abyss) return infinit;
			
			return 15000;
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
            	//cout << "--Start-- " << i << ", " << j << endl;
            	
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
					//cout <<"add " << "(" << arc.first << ", " << arc.second << ") to verice:" << ver << endl;
            		G[ver].push_back(arc);
            		
            		//cout << "Edge to cell: " << p.i << ", "<< p.j << "Vertice "<< arc.second<<" Weight: " << arc.first << endl;
            		
            	}

				
				//cout << "Done i,j: "<< i << ", " << j<< endl;
            }
            //cout << "Done i:  " << i << endl;
    	}
    	return G;
    }

//-----Move Dwarve towards d-------

void move_dwarve(int id, int s, int dest, vector<int>& parent){
	
	int i = dest;
	cout << dest << "<-";
	while(parent[i] != s){
		i= parent[i];
		cout << i << "<-";
	}
	int next = i;
	i = parent[i];
	cout << "vert: " << i << endl;
	Pos p = vertopos(i);
	
	cout << i << endl;
	Pos pnext = vertopos(next);
	int deltax =  pnext.j - p.j;
	int deltay = pnext.i - p.i;
	cout << "Moving dwarve "<< id << " at "<< p.i<< ", " << p.j<<" towards "<< vertopos(dest)<< endl;
	cout << "I'm at: " << unit(id).pos << endl;
	cout <<"deltax: "<< deltax<<" deltay: " << deltay << endl;
	Dir d = Right;
	if(deltax < 0 and deltay < 0) {
		cout << "I'm dwarve " << id << " going TL" << endl;
		command(id,TL);
	}
	else if(deltax < 0 and deltay > 0)
	{
		cout << "I'm dwarve " << id << " going LB" << endl;
		command(id,LB);
	} 
	else if(deltax > 0 and deltay < 0)
	{
		cout << "I'm dwarve " << id << " going RT" << endl;
		command(id,RT);
	}  
	else if(deltax > 0 and deltay > 0){
		cout << "I'm dwarve " << id << " going BR" << endl;
		command(id,BR);
	}  
	
	else if(deltax == 0 and deltay > 0){
		cout << "I'm dwarve " << id << " going Bottom" << endl;
		command(id,Bottom);
	}   
	else if(deltax == 0 and deltay < 0){
		cout << "I'm dwarve " << id << " going Top" << endl;
		command(id,Top);
	} 
	else if(deltax < 0 and deltay == 0){
		cout << "I'm dwarve " << id << " going Left" << endl;
		command(id,Left);
	}  
	else if(deltax > 0 and deltay == 0){
		cout << "I'm dwarve " << id << " going Right" << endl;
		command(id,Right);
	}   
	cout << "Now I'm at " << unit(id).pos << endl;
	//cout << "Moving: " << id << " at " << postover(p)<<" towards vertex: " << dest <<" trough "<< next << endl;
	
}


//-----Clost tresure----

int cls_treasure(vector<double>& d, int x){
	int min =5;
	int n = d.size();
	for(int i=0; i<n;++i){
		Cell c = cell(vertopos(i));
		if(d[i]<d[min] and c.treasure) min = i;
	}
	return min;
}


//---cls_granite

int cls_granite(vector<double>& d, int x){
	int min =5;
	int n = d.size();
	for(int i=0; i<n;++i){
		Cell c = cell(vertopos(i));
		if(d[i]<d[min] and c.type == Granite) min = i;
	}
	return min;
}


//true if cell is in path



bool path(Pos p, int id, int s, int dest, vector<int>& parent){
	bool found = false;
	int n = parent.size();
	for(int i=0; i<n; ++i){
		if(postover(p) == parent[i]) return true;
	}
	return found;
}
//----Print Graph---

//typedef vector<vector<WArc>> WGraph;	typedef pair<double, int> WArc


void print_grid(int id, int s, int dest, vector<int>& parent){
	
	
	vector<int> v;
	int i= dest;
	while(parent[i] != s){
		v.push_back(parent[i]);
		i = parent[i];
	}
	
	
    Pos p;
	for(p.i= 0; p.i<60; ++p.i){
	
	
            for(p.j=0; p.j<60; ++p.j){
            	double w = weight(p);
            	if(w == infinit)  cout << "|"<<"\033[1;31mi\033[0m" << "|-";
            	else if(w == 0) cout << "|"<< "\033[1;32mt\033[0m"  <<"|-";
            	else if(path(p, id, s, dest, v)) cout << "|"<<"\033[1;35mp\033[0m"<< "|-";
            	//else if(cell(p).owner == me()) cout << "|"<<"\033[1;37mp\033[0m"<< "|-";
            	else if(w == 20) cout << "|"<<"\033[1;40mr\033[0m"<< "|-";
            	else  cout << "|v|-";
            	
            }
            cout << endl;
    }
}


int cls_maze(vector<double>& d, int x){
	double ratio=0;
	int total =0;
	int trea = 0;
	vector<int> vr;
	for(int i=0; i<12;++i){
		for(int j=0; j<12;++j){//Per cada 10x10
		ratio=0;
		total =0;
		trea = 0;
		Pos p;
		for(int l=0; l<5;++l){//mira les 100 caselles i conta els tresors
			for(int h=0; h<5; ++h){
				++total;
				p.i = 5*i + l;
				p.j = 5*j +h;
				if(cell(p).treasure)++trea;
			}
		}
		ratio = trea/total;
		vr.push_back(ratio);
		}
	}
	int pmax = 0;
	for(int c=0; c<vr.size(); ++c){
		if(vr[c]>vr[pmax]) pmax = c;
	}
	

	return 0;
}




//----------BFS-----







/* ---------------------------------------CELL INFO-----------------------------------------*/









  /**
   * Play method, invoked once per each round.
   */
	virtual void play () {
		cout << "--My Turn---" << endl;
		WGraph G = gridtograph();
		cout << "---Grid To Graph Created---" << endl;
		//print_grid();
		vector<double> d;
		vector<int> p;
		int x, y;
		
		vector<int> aux =  dwarves(me());
		int n = aux.size();
		cout << "--Dwarves: "<< n <<" — " << endl;
		for(int i = 0; i<n;++i){
		//fOR EACH DWARVE
			cout << "starrt dwarve " << i <<endl;
			cout << " x as pos" <<unit(aux[i]).pos << endl;
			x = postover(unit(aux[i]).pos);
			cout << " x as ver" <<x << endl;
			dijkstra(G, x, d, p);
			Pos e(35,30);
//			
			//if(i==0) print_grid(i, x, y, p);
			
			
			vector<Pos> destinos;
			
			for(int r=0; r<200; ++r){
				e.i = random(22,28);
				e.j = random(25,47);
				destinos.push_back(e);
			}
			
			y = postover(destinos[i]);
			
	
			/**else {
				e.i = random(0,59);
				e.j = random(0,59);
				y = postover(e);
			}**/
			
			move_dwarve(aux[i],x, y, p);
			
			cout << endl;
		}
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
