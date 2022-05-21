// Demonstration of Hardy-Weinberg Equilibrium

#include <stdio.h>
#include <stdlib.h>

const int POP = 1000000; // Population size
const int NUM_GENS = 100; // Number of generations simulated
const float domPercent = 0.2; // Percent of alleles in the population which are dominant
const char domChar = 'A'; // Character representing dominant allele
const char resChar = 'a'; // Character representing recessive allele

typedef struct org org;
struct org{ // Each organism is diploid
    char allele1;
    char allele2;
};

void nextGen(org orgs[]){ // Takes an input of organism structs, selects the same number of pairs to reproduce sexually, and creates the next generation from their offspring
    org newOrgs[POP];
    for(int i = 0; i < POP; i++){
        org parent1 = orgs[rand()%POP];
        org parent2 = orgs[rand()%POP];
        org newOrg;
        if(rand() % 2 == 0){
            newOrg.allele1 = parent1.allele1;
        }
        else{
            newOrg.allele1 = parent1.allele2;
        }
        if(rand() % 2 == 0){
            newOrg.allele2 = parent2.allele1;
        }
        else{
            newOrg.allele2 = parent2.allele2;
        }
        newOrgs[i] = newOrg;
    }
    for(int i = 0; i < POP; i++){
        orgs[i] = newOrgs[i];
    }
}

void printPopData(org orgs[]){ // Prints gene pool and genotype statistics
    int alleleDomCount = 0;
    int alleleResCount = 0;
    int hDomCount = 0;
    int hetCount = 0;
    int hResCount = 0;
    for(int i = 0; i < POP; i++){
        int res1 = 0;
        int res2 = 0;
        if(orgs[i].allele1 == domChar){
            alleleDomCount++;
        }
        else if(orgs[i].allele1 = resChar){
            alleleResCount++;
            res1 = 1;
        }
        
        if(orgs[i].allele2 == domChar){
            alleleDomCount++;
        }
        else if(orgs[i].allele2 = resChar){
            alleleResCount++;
            res2 = 1;
        }
        
        if(res1 && res2){
            hResCount++;
        }
        else if(res1 || res2){
            hetCount++;
        }
        else{
            hDomCount++;
        }
    }
    printf("\nGene pool: %.2f%% dominant (%c), %.2f%% recessive (%c).", 50.0*alleleDomCount/POP, domChar, 50.0*alleleResCount/POP, resChar);
    printf("\n Genotypes: %.2f%% homozygous dominant, %.2f%% heterozygous, %.2f%% homozygous recessive.", 100.0*hDomCount/POP, 100.0*hetCount/POP, 100.0*hResCount/POP);
}

int main(){
    org orgs[POP];
    for(int i = 0; i < POP; i++){ // Generate organism array
        org newOrg;
        newOrg.allele1 = 'a';
        if(rand() < domPercent*RAND_MAX){
            newOrg.allele1 = 'A';
        }
        newOrg.allele2 = 'a';
        if(rand() < domPercent*RAND_MAX){
            newOrg.allele2 = 'A';
        }
        orgs[i] = newOrg;
    }
    
    printPopData(orgs);
    for(int i = 0; i < NUM_GENS; i++){ // Iterate through the generations and see how close they are to H-W equilibrium
        nextGen(orgs);
        printPopData(orgs);
    }

    return 0;
}
