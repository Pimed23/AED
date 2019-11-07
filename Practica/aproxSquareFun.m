function aproxSquareFun( x, y )
  n = size( x, 1 );
  sumX = 0; sumY = 0; sumX2 = 0; sumX3 = 0; sumX4 = 0; sumXY = 0; sumX2Y = 0;
  for i = 1 : n
    sumX += x( i );
    sumY += y( i );
    sumX2 += x( i ) * x( i );
    sumX3 += x( i ) * x( i ) * x( i );
    sumX4 += x( i ) * x( i ) * x( i ) * x( i ); 
    sumXY += x( i ) * y( i );
    sumX2Y += x( i ) * x( i ) * y( i );
  end
  
  a = [ sumX2 sumX n; sumX3 sumX2 sumX; sumX4 sumX3 sumX2 ]
  b = [ sumY; sumXY; sumX2Y ]
  S = inv( a ) * b;
  A = S( 1 )
  B = S( 2 )
  C = S( 3 )

end