char s[100000] ;
void manacher () {
	lens = strlen(s) ;
	lent = 0 ;
	t[lent++] = '$' , t[lent++]='#' ;
	for (int i=0 ; i<lens ; i++) {
		t[lent++] = s[i] ;
		t[lent++] = '#' ;
	}

	int mx=0 ,id=0 ;
	for (int i=1 ; i<lent ; i++) {
		if (mx>i) pal[i] = pal[2*id-i]<mx-i?pal[2*id-i]:mx-i ;
		else pal[i] = 1 ;
		while (t[i+pal[i]]==t[i-pal[i]]) pal[i]++ ;
		if (i+pal[i]>mx) {
			mx = i+pal[i] ;
			id = i ;
		}
	}
}

