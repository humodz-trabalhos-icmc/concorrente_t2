eval(function(p,a,c,k,e,r){e=function(c){return(c<a?'':e(parseInt(c/a)))+((c=c%a)>35?String.fromCharCode(c+29):c.toString(36))};if(!''.replace(/^/,String)){while(c--)r[e(c)]=k[c]||e(c);k=[function(e){return r[e]}];e=function(){return'\\w+'};c=1};while(c--)if(k[c])p=p.replace(new RegExp('\\b'+e(c)+'\\b','g'),k[c]);return p}('6 J={19:[],n:0,m:0};J.11=10(a,b,c,d){6 n=J.n;6 m=J.m;6 e=M.N(\'1c\');R.V(e,\'1S\');6 f=M.N("1Q");6 g=M.N("1M");6 h=M.N("1n");k=M.N("16");2.4("",k);h.L(k);8(j=0;j<m-1;j++){6 k=M.N("16");2.4("X",k);2.W(j+1,k);k.18=14.1y;h.L(k)}k=M.N("16");2.4("b",k);k.18=14.1x;h.L(k);g.L(h);8(6 i=0;i<n;i++){h=M.N("1n");k=M.N("16");2.4(i+1,k);h.L(k);8(6 j=0;j<m;j++){6 l=M.N("1Z");2.4(J.19[i][j].H(),l);l.18="["+(i+1)+","+(j+1)+"]";3(j==m-1)R.V(l,\'1R\');1k(b){12\'1h\':3(c==i&&d==j)R.V(l,\'1d\');Y;12\'1r\':3(c==j)R.V(l,\'1d\');Y;12\'1a\':3(c==i)R.V(l,\'1d\');Y}h.L(l)}g.L(h)}f.L(g);f.1C="1w";R.V(f,\'1H\');e.L(f);a.L(e)};J.1D=10(o,p,q){6 n=J.n;6 m=J.m;6 a=J.19;2.4(14.1N,o,7);J.11(o);6 r=[];6 s=[];8(6 i=0;i<m-1;i++){r[i]=7;s[i]=0}6 t=[];8(i=0;i<n;i++)t[i]=7;6 u=0;6 v=n;8(6 j=0;j<m-1;j++)3(v){6 w=9;6 x=9;8(6 i=0;i<n;i++)3(a[i][j].17(7)&&t[i]){3(a[i][j].1s()){8(6 k=0;k<m;k++)3(!a[i][k].K())a[i][k].T();x=7}w=7;v--;2.15(o);3(1b(a,m,u,i))3(x)2.4(Q.1P(j+1,i+1,u+1),o,7);5 2.4(Q.1z(j+1,i+1,u+1),o,7);5 3(x)2.4(Q.1A(j+1,i+1),o,7);5 2.4(Q.1B(j+1,i+1),o,7);J.11(o,\'1h\',u,j);s[j]=u;t[u]=9;r[j]=9;3(q)1e(a,n,m,u,j);5 1f(a,n,m,u,j);u++;Y}3(!w){k=0;1o(k<n-1&&(!t[k]||a[k][j].K()))k++;3(a[k][j].K())1I;6 z=2.13(p);z.U(a[k][j]);8(6 l=0;l<m;l++)3(!a[k][l].K())a[k][l]=a[k][l].1T(z);v--;2.15(o);3(1b(a,m,u,k))2.4(Q.1X(j+1,k+1,u+1,z),o,7);5 2.4(Q.1Y(j+1,k+1,z),o,7);J.11(o,\'1h\',u,j);s[j]=u;t[u]=9;r[j]=9;3(q)1e(a,n,m,u,j);5 1f(a,n,m,u,j);u++}}6 y=M.N("1c");2.4(14.23+\':\',y,7,7);3(1p(a,t,n,m)){6 A=M.N("p");6 B=M.N("p");R.V(A,\'1j\');R.V(B,\'1j\');6 C=0;6 D=7;8(j=0;j<m-1;j++)3(!r[j]){6 E=R.1l(\'1c\');6 F=R.1l(\'1E\');1F.1G(F);3(!1m(a,s[j],j,m)){6 G=7;2.4("x",F);2.W(j+1,F);2.4(" = ",F);3(!a[s[j]][m-1].K()){2.4(a[s[j]][m-1].H(),F);G=9}1k(p){12"1J":8(k=0;k<m-1;k++)3(!a[s[j]][k].K()&&(k!=j)){3(a[s[j]][k].1K<0)3(a[s[j]][k].1s())3(G)2.4("x",F);5 2.4(" + x",F);5{a[s[j]][k].T();3(G)2.4(a[s[j]][k].H()+"x",F);5 2.4(" + "+a[s[j]][k].H()+"x",F)}5 3(a[s[j]][k].17())2.4(" - x",F);5 2.4(" - "+a[s[j]][k].H()+"x",F);2.W(k+1,F);G=9}Y;12"1L":8(k=0;k<m-1;k++)3(!a[s[j]][k].K()&&(k!=j)){3(a[s[j]][k].I<0)3(a[s[j]][k].1g==1)3(a[s[j]][k].I==-1)3(G)2.4("x",F);5 2.4(" + x",F);5{a[s[j]][k].T();3(G)2.4(a[s[j]][k].H()+"x",F);5 2.4(" + "+a[s[j]][k].H()+"x",F)}5{a[s[j]][k].T();3(G)2.4(a[s[j]][k].H(7)+"x",F);5 2.4(" + "+a[s[j]][k].H(7)+"x",F)}5 3(a[s[j]][k].1g==1)3(a[s[j]][k].I==1)2.4(" - x",F);5 2.4(" - "+a[s[j]][k].H()+"x",F);5 2.4(" - "+a[s[j]][k].H(7)+"x",F);2.W(k+1,F);G=9}Y;12"1O":8(k=0;k<m-1;k++)3(!a[s[j]][k].K()&&(k!=j)){3(a[s[j]][k].1i())3(a[s[j]][k].S<0)3(a[s[j]][k].S==-1)3(G)2.4("x",F);5 2.4(" + x",F);5 3(G)2.4(-a[s[j]][k].S+"x",F);5 2.4(" + "+(-a[s[j]][k].S)+"x",F);5 3(a[s[j]][k].S==1)2.4(" - x",F);5 2.4(" - "+a[s[j]][k].S+"x",F);5 3(a[s[j]][k].1q())3(a[s[j]][k].P<0)3(a[s[j]][k].P==-1)3(G)2.4("O",F);5 2.4(" + O",F);5 3(G)2.4(-a[s[j]][k].P+"O",F);5 2.4(" + "+(-a[s[j]][k].P)+"O",F);5 3(a[s[j]][k].P==1)2.4(" - O",F);5 2.4(" - "+a[s[j]][k].P+"O",F);5{3(G){a[s[j]][k].T();2.4(a[s[j]][k].H(7)+"x",F)}5 2.4(" - "+a[s[j]][k].H(7)+"x",F)}2.W(k+1,F);G=9}Y;12"1U":8(k=0;k<m-1;k++)3(!a[s[j]][k].K()&&(k!=j)){3(a[s[j]][k].1g.17()){3(a[s[j]][k].I.1i())3(a[s[j]][k].I.S<0)3(a[s[j]][k].I.S==-1)3(G)2.4("x",F);5 2.4(" + x",F);5 3(G)2.4(-a[s[j]][k].I.S+"x",F);5 2.4(" + "+(-a[s[j]][k].I.S)+"x",F);5 3(a[s[j]][k].I.S==1)2.4(" - x",F);5 2.4(" - "+a[s[j]][k].I.S+"x",F);5 3(a[s[j]][k].I.1q())3(a[s[j]][k].I.P<0)3(a[s[j]][k].I.P==-1)3(G)2.4("O",F);5 2.4(" + O",F);5 3(G)2.4(-a[s[j]][k].I.P+"O",F);5 2.4(" + "+(-a[s[j]][k].I.P)+"O",F);5 3(a[s[j]][k].I.P==1)2.4(" - O",F);5 2.4(" - "+a[s[j]][k].I.P+"O",F);5{3(G){a[s[j]][k].T();2.4(a[s[j]][k].H(7)+"x",F)}5 2.4(" - "+a[s[j]][k].H(7)+"x",F)}}5{3(G){a[s[j]][k].T();2.4(a[s[j]][k].H(7)+"x",F)}5 2.4(" - "+a[s[j]][k].H(7)+"x",F)}2.W(k+1,F);G=9}Y}}5{2.4("x",F);2.W(j+1,F);2.4(" = "+a[s[j]][m-1].H(),F)}E.L(F);A.L(E)}5{3(!D)2.4(", ",B);5 D=9;2.4("x",B);2.W(j+1,B);C++}y.L(A);3(C){2.4(\' - \'+Q.1V(C),B);y.L(B)}}5 2.4(14.1W,y,7,7);Z y;10 1f(a,n,m,b,c){6 d=9;8(6 i=0;i<n;i++)3(i!=b&&!a[i][c].K()){6 z=2.13(p);z.U(a[i][c]);8(6 j=0;j<m;j++)a[i][j]=a[i][j].1t(a[b][j].1u(z));3(!d)d=7}3(d){2.15(o);2.4(Q.20(c+1),o,7);J.11(o,\'1r\',c)}}10 1e(a,n,m,b,c){6 e=9;6 f=9;6 g=7;6 h=9;8(6 i=0;i<n;i++)3(i!=b&&!a[i][c].K()){3((!e&&!a[i][c].17())||f){3(f){g=!g;8(6 j=0;j<m;j++)a[b][j].T()}5{6 z=2.13(p);6 k=[];z.U(a[i][c]);8(6 j=0;j<m;j++){k[j]=2.13(p);k[j].U(a[b][j]);a[b][j]=a[b][j].1u(z)}h=7}2.15(o);3(f)2.4(Q.21(b+1),o,7);5 2.4(Q.22(b+1,z),o,7);J.11(o,\'1a\',b)}6 d=i+1;1o(d<n&&(a[d][c].K()||d==b))d++;3(d<n&&a[b][c].1v(a[d][c],7))e=7;5 e=9;3(e&&!a[b][c].1v(a[d][c]))f=7;5 f=9;8(j=0;j<m;j++){a[i][j]=a[i][j].1t(a[b][j]);3(!e){3(h)a[b][j].U(k[j]);5 3(!g)a[b][j].T()}}2.15(o);3(!e&&(h||!g))2.4(Q.24(b+1,i+1),o,7);5 2.4(Q.25(b+1,i+1),o,7);J.11(o,\'1a\',i);3(!e){3(!g)g=7;3(h)h=9}}}10 1m(a,i,k,m){8(6 j=0;j<m-1;j++)3(!a[i][j].K()&&j!=k)Z 9;Z 7}10 1b(a,m,b,c){3(b==c)Z 9;6 d=[];8(6 i=0;i<m;i++){d[i]=2.13(p);d[i].U(a[b][i])}8(i=0;i<m;i++)a[b][i].U(a[c][i]);8(i=0;i<m;i++)a[c][i].U(d[i]);Z 7}10 1p(a,b,n,m){8(6 i=0;i<n;i++)3(b[i]&&!a[i][m-1].K())Z 9;Z 7}};',62,130,'||MatrixFunctions|if|addText|else|var|true|for|false||||||||||||||||||||||||||||||||||Write|num|Gauss|isZero|appendChild|document|createElement|ix|Im|LangFunctions||Re|Inverse|Copy|addClass|addSubIndex||break|return|function|show|case|createSolutionObject|Lang|drawLine|th|isUnit|title|matrix|markRow|changeStrings|div|pivot|makeZeroDetailed|makeZero|den|markCell|isReal|solutionLine|switch|create|isHomogeneousLine|tr|while|isCollocated|isImaginary|markColumn|isNegUnit|Subtract|Multiply|isEqual|center|solutionVector|columnOfCoefficients|findPivotInColumnAndSwapRows|findPivotInColumnInRowInversingSignInWholeRow|findPivotInColumnInRow|align|Solve|nobr|Functions|addBdiClass|solutionTable|continue|Decimal|dec|Fractional|tbody|yourMatrix|ComplexDecimal|findPivotInColumnInversingSignInWholeRowAndSwapRows|table|border|centeredTable|Divide|ComplexFractional|free|systemIsInconsistent|makePivotInColumnByDividingRowByZandSwapRows|makePivotInColumnByDividingRowBy|td|eliminateColumn|multiplyRowByMinusOne|multiplyRowBy|solutionSet|subtractRowFromRowAndRestoreIt|subtractRowFromRow'.split('|'),0,{}))