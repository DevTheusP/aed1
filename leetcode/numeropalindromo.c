bool isPalindrome(int x) {
    if(x < 0 || (x % 10 == 0 && x != 0)){
        return false;
    }
    int metadereversa = 0;
    while(x > metadereversa){
        metadereversa = metadereversa * 10 + x % 10;
        x = x / 10;
    }
    return x == metadereversa || x == metadereversa/10;

}