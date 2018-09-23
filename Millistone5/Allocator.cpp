/**********************************************************
  * Name: Yuru Ciou
  * Student ID: 115895179
  * Seneca email: yciou@myseneca.ca
  * Date of Completion: 2018/08/06
  **********************************************************/
#include "Product.h"
#include "Perishable.h"

namespace AMA {
    
    // creates an empty product
    //
    iProduct* CreateProduct() {
        return new Product();
    }
    
    // creates an empty perishable product
    //
    iProduct* CreatePerishable() {
        return new Perishable();
    }
}
