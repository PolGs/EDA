
#include "Player.hh"

using namespace std;


/**
 * Write the name of your player and save this file
 * as AI<name>.cc
 */
#define PLAYER_NAME mexeruss





struct PLAYER_NAME : public Player {


    /**
     * Factory: returns a new instance of this class.
     * Do not modify this function.
     */
    static Player* factory () {
        return new PLAYER_NAME;
    }
    

    /**
     * Attributes for your player can be defined here.
     */     


    /**
     * Play method.
     * 
     * This method will be invoked once per each round.
     * You have to read the board here to place your actions
     * for this round.
     *
     */
     
     
     struct Casilla{
    int val;
    Pos pos;
    
    bool operator<(const Casilla& rhs) const{
        return rhs.val > val;
    }
    bool operator==(const Casilla& rhs) const{
        return rhs.val == val;
    }
    bool operator>(const Casilla& rhs) const{
        return rhs.val < val;
    }
    

};

struct Movement{
    pair<int,int> offset;
    double weight;

};
          
typedef priority_queue<Casilla, vector<Casilla>,greater<Casilla> > cola;
  
  
double dist(Pos a, Pos b){
    double deltax = first(a) - first(b);
    double deltay = second(a) - second(b);
    return sqrt(deltax*deltax + deltay*deltay);
}

  
     
vector<vector<double>> updatewmatrixgas(Pos carpos, int cid){
    vector<Pos> d;
    d.push_back(complex<int>(1,0));
    d.push_back(complex<int>(-1,0));
    d.push_back(complex<int>(0,-1));
    
    int n = number_rows();
    int m = number_universe_columns();

    vector<vector<double> > M(n,vector<double> (m));

    
    cola c;

    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            M[i][j] = -1;        
        }
     }



    double mindis = 9999;
    Casilla a;
    int lastc = 0;
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
             Pos p(i,j);;
            if(cell(p).type == WATER_BONUS or (cell(p).type == GAS_BONUS and car(cid).gas < 80)){
                a.pos = p;
                a.val = 0;
                mindis = dist(carpos,p);
                c.push(a);
                if(j > lastc) lastc = j;
            }
        }
    }
    
             
    
    
    while(not c.empty()){
        Casilla t = c.top();
        c.pop();
        if(M[first(t.pos)][second(t.pos)] < 0){
            M[first(t.pos)][second(t.pos)] = t.val;
            for(int i=0; i<3; ++i){
                Pos p = t.pos;
                p+=d[i];
                if(within_universe(p)){
                    Casilla caux;
                    if(cell(p).type == TYRE or cell(complex<int>(first(p),second(p)-2)).type ==MISSILE or (cell(p).type == CAR and cell(p).cid != cid)) caux.val = 1000;
                    else caux.val = t.val + 1;
                    caux.pos = p;
                    c.push(caux);
                }
            }
        }
    }
    
    if(lastc != m-1){
        int ncd = m - lastc ;
        for(int i=0; i<n; ++i){
            for(int j=1; j< ncd; ++j){
                M[i][lastc+j] = M[i][0]+ncd-j;
            }
        }
        
        
    }
    
    return M;
     

}

    
     
     
     
void printmatrix(vector<vector<double>> a){
        int n = a.size();
        int m = a[0].size()/2;
        for(int i=0; i<n;++i){
            for(int j=0; j<m; ++j){
                if(a[i][j] < 10) cout   << "|000"<< a[i][j];
                else if(a[i][j] < 100)cout   << "|00"<< a[i][j];
                else if(a[i][j] < 1000)cout   << "|0"<< a[i][j];
                else cout   << "|XXXX";
            }
            cout << "|"<<endl<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
        }
     }
     
   
int min_dir_pos(vector<Movement> v){
    int n=v.size();
    int minpos = 0;
    for(int i=1; i<n; ++i){
        if(v[i].weight<v[minpos].weight) minpos = i;
    }
    return minpos;
}


Dir best_dir(vector<Movement> vm,vector<vector<double>> M,Pos p){

             
              bool found = 0;
              Dir bdir = DEFAULT;
               
              while(not found){

                    int minpos = min_dir_pos(vm);
                    
                    
                    if(vm[minpos].offset.first == 1 and vm[minpos].offset.second == 0){
                        found = 1;
                        bdir = SLOW_DOWN;
                    }
                    
                   if(vm[minpos].offset.first == -1 and vm[minpos].offset.second == 0){
                        found = 1;
                        bdir = SLOW_UP;
                    } 
                    
                    if(vm[minpos].offset.first == 0 and vm[minpos].offset.second == 1){
                        found = 1;
                        bdir = DEFAULT;
                    }
                    
                    if(vm[minpos].offset.first == 0 and vm[minpos].offset.second == 0){
                        found = 1;
                        bdir = SLOW;
                    }
                                 

                    if(vm[minpos].offset.first == 1 and vm[minpos].offset.second == 2){//
                        if(M[first(p)][second(p)+1]<999 and M[first(p)+1][second(p)+1]<999 and M[first(p)+1][second(p)]<999 and M[first(p)][second(p)+2]<999){//BOTTOM right -- (1,2)
                            found = 1;
                            bdir = FAST_DOWN;
                        }
                        else vm.erase(vm.begin()+minpos);
                     }
                     
                     else if(vm[minpos].offset.first == -1 and vm[minpos].offset.second == 2){//

                            if(M[first(p)][second(p)+1]<999 and M[first(p)-1][second(p)+1]<999 and M[first(p)-1][second(p)]<999 and M[first(p)][second(p)+2]<999){//topright -- (-1,2)
                                found = 1;
                                bdir = FAST_UP;
                            }
                            else vm.erase(vm.begin()+minpos);
                        }
                         
                     else if(vm[minpos].offset.first == -1 and vm[minpos].offset.second == 1){//
                        if(M[first(p)][second(p)+1]<999 and M[first(p)-1][second(p)]<999){//top mid -- (-1,1)
                            found = 1;
                            bdir = UP;
                        }
                        else vm.erase(vm.begin()+minpos);
                     }
                     else if(vm[minpos].offset.first == 1 and vm[minpos].offset.second == 1){//
                        if(M[first(p)][second(p)+1]<999 and M[first(p)+1][second(p)]<999){//bot mid -- (1,1)
                            found = 1;
                            bdir = DOWN;
                        }
                        else vm.erase(vm.begin()+minpos);
                     }
                     
                     else if(vm[minpos].offset.first == 0 and vm[minpos].offset.second == 2){//
                        if(M[first(p)][second(p)+1]<999){//mid right -- (0,2)
                            found = 1;
                            bdir = FAST;
                         }
                         else vm.erase(vm.begin()+minpos);
                    }
                    
                    
                    
                 }
                 //cout << "In round " << round() << "im in position" << p << "taking direction " << bdir<<endl;
                 return bdir;
                 
}
   



    
    
     
vector<Movement> get_adj_vec(vector<vector<double>> M, Pos p){           
           
            vector<Movement> vm;
            
            for(int i=0; i<3 ;++i){
                 for(int j=0; j<3;++j){
                    Pos s(first(p)-1+i,second(p)+j);
                    if(within_universe(s)){                  
                      Movement m;
                      m.offset.first = i-1;
                      m.offset.second = j;
                      m.weight = M[first(s)][second(s)];
                      vm.push_back(m);
                     }  
                  }
              }            
              return vm;
}
     
     
     
     
void movecars(){
     	int c=0;
	Pos pfin;
        for (Car_Id cid = begin(me()); cid != end(me()); ++cid) {
     
        Pos p = car(cid).pos;
	pfin = p;
        
        vector<vector<double>> a = updatewmatrixgas(p,cid);
        
        //printmatrix(a);
            
        vector<Movement> vm = get_adj_vec(a,p);

        
        Dir bd = best_dir(vm,a,p);
	if(bd == DEFAULT ) shoot(cid);
	
        else {
		if()
		pfin = car(cid).pos + bd;
		Action::move(cid,bd);

		
	}
	c++;
        }
    } 
     
     
     
    virtual void play () {
    
        if(round()<3){
            int c=0;
            for (Car_Id cid = begin(me()); cid != end(me()); ++cid) {
               if(c%2==0) move(cid,FAST_UP);
               else move(cid,FAST_DOWN); 
               ++c;
               } 
        }
        else movecars();
    
       

    
    
    }

    
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

