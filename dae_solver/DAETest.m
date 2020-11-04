% Pendulum DAE and Jacobian defined at the end.
% Set consistent initial conditions.
g = 9.80665;
theta = pi/4;
x = sin(theta);
y = -cos(theta);
u = 0.; v = 0.;
lam = g*cos(theta);
q0 = [x; y; u; v; lam];

% Create an instance of the DAE solver class.
solver = DAESolver;

% Call the integrate method.
ndiff = 4; nalg = 1;
[t, sol] = solver.integrate(ndiff, nalg, @DAEFun, @DAEJac, q0, 0., 10., 1e-3);

% Plot the variables as a function of t (columns of the array sol).
% Your code here %

% Optional: In the function and Jacobian for the simple pendulum,
% replace the algebraic constraint on length (index 3 formulation)
% with either the index 2 or index 1 constraint formulations.
% Integrate the DAE and plot the three constrained quantities.
% Do you see evidence of higher fluctuation or drift in the constraints
% that are not explicitly enforced?

% Functions %
%-----------%
function f = DAEFun(t,q)
    g = 9.80665;
    x = q(1); y = q(2); u = q(3); v = q(4); l = q(5);
    f = [u; v; -l*x; -(l*y+g); x*x + y*y - 1];
end

function j = DAEJac(t,q)
    x = q(1); y = q(2); u = q(3); v = q(4); l = q(5);
    j = [ 0, 0, 1, 0, 0;
          0, 0, 0, 1, 0;
         -l, 0, 0, 0,-x;
          0,-l, 0, 0,-y;
         2*x,2*y,0, 0, 0;];
end
