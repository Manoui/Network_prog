#include "network.h"
#include "random.h"
#include "iostream"
using namespace std;

    void Network::resize(const size_t &n){
		values.resize(n);//rajouter des noeuds ou en enlever
		RNG.normal(values,0,1);
	}
	
	

    bool Network::add_link(const size_t& indiceA, const size_t& indiceB){
		
		//a ne peut pas faire lien avec a
		if(indiceA == indiceB){return false;}
		
		//indiceA et indiceB doivent être dans tableau  //pas plus de lien que de valeurs
		if(indiceA >= size() or indiceB >= size()){return false;}
		
		//lien est fait seulement si pas déjà présent
		auto range = links.equal_range(indiceA);
		for (auto it=range.first; it!=range.second; ++it){
			if(it->second == indiceB){ return false;} 
		}
		
		
		//lien bidirectionnel: à partir de a 
		links.insert(pair<const size_t&,const size_t&>(indiceA,indiceB)); 
		links.insert(pair<const size_t&,const size_t&>(indiceB,indiceA)); 
		return true;
	}
	


   size_t Network::random_connect(const double& mean_deg){
	 links.clear();
	  
	 for(size_t i(0); i<size() ; ++i){                                         
		 int nb_liens(RNG.poisson(mean_deg)); 
		 while(nb_liens>=size()-1){ 
			 nb_liens=RNG.poisson(mean_deg);
		}
		
		int nb(0);  
		
			 
	                       
			 while(nb<nb_liens){   
				int indice=RNG.uniform_double(0, size()-1);       
				if(add_link(i, indice)){
				 ++nb;
				}
			}

		 
	 }
	 return links.size()/2;
 }
		
		

    size_t Network::set_values(const std::vector<double>& new_values){
		size_t values_to_add(min(new_values.size(), size())); 
		
		
		for(size_t i(0); i<values_to_add; ++i){
			values[i]=new_values[i];
		}
		
		return values_to_add;
	}
    


    size_t Network::size() const{
		return values.size();
	}
    

    size_t Network::degree(const size_t &_n) const{
		return links.count(_n);
	}
    


    double Network::value(const size_t &_n) const{
		if(_n>= size()){
			return 0;
		}
		return values[_n];
		
	}


    std::vector<double> Network::sorted_values() const{
		vector<double> ordered;
		
		for(auto i: values){
			ordered.push_back(i);
		}
		
		sort(ordered.begin(), ordered.end(), greater<double>());
		return ordered;
	}
		


    std::vector<size_t> Network::neighbors(const size_t& indice) const{
		vector<size_t> neighbors;
		if(indice >= size()){
			return neighbors;
		}
		
		auto range = links.equal_range(indice);
		
		for (auto it=range.first; it!=range.second; ++it){
			neighbors.push_back(it->second);
		}
		return neighbors;
	}



