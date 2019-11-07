function noStraightMinSquare( X, y )
  n = size( X, 1 );
  sumX = 0; sumY = 0; prodXY = 0; squareX = 0;
  for i = 1 : n
    sumX = sumX + X( i );
    sumY = sumY + log( y( i ));
    prodXY = prodXY + X( i ) * log( y( i ));
    squareX = squareX + X( i ) * X( i );
  end
  A = [ sumX n; squareX sumX ];
  b = [ sumY; prodXY ];
  S = inv( A ) * b;
  m = S( 1 )
  b = S( 2 )
  c = exp( b )
end