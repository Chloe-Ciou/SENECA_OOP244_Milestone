/**********************************************************
  * Name: Yuru Ciou
  * Student ID: 115895179
  * Seneca email: yciou@myseneca.ca
  * Date of Completion: 2018/07/31
  **********************************************************/
#include "MyProduct.h"

namespace AMA {
    
    iProduct* CreateProduct() {
        return new MyProduct("Product");
    }
    iProduct* CreatePerishable() {
        return new MyProduct("Perishable");
    }
}

