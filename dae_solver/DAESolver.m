classdef DAESolver
    properties
        % Backward differentiation formula coefficients.
        a = {-1.,[1./3;-4./3],[-2./11; 9./11; -18./11]}
        b = [1., 2./3, 6./11]
        m {mustBeNumeric}  % number of differential variables
        n {mustBeNumeric}  % number of algebraic variables
    end
    methods
        function [t,sol] = integrate(obj, m, n, fun, jac, yi, ti, tf, dt)
            %{
            Routine to run DAE integration.
            m,n - the number of differential and algebraic degrees of freedom, respectively.
            fun, jac - the system of equations to integrate, and its jacobian.
            yi - the initial condition.
            ti, tf - initial and final integration times.
            dt - the step size to use.
            %}

            % Save the number of differential and algebraic variables as class properties.
            obj.m = m;
            obj.n = n;

            % Compute number of integration steps to pre-allocate memory for the solution output:
            nsteps = int32(round((tf-ti)/dt)) + 1;
            t = zeros(nsteps,1);
            sol = zeros(nsteps, m+n);

            % Set initial condition.
            sol(1,:) = yi;

            % First step: 1st order BDF
            sol(2,:) = obj.newton(1, fun, jac, ti+dt, dt, sol(1,:), sol(1,:));
            t(2) = ti + dt;

            % Second step: 2nd order BDF
            sol(3,:) = obj.newton(2, fun, jac, ti+2*dt, dt, sol(2,:), sol(1:2,:));
            t(3) = ti + 2*dt;

            % Resume with 3rd order BDF
            k = 3;
            while ti + k*dt <= tf
                sol(k+1,:) = obj.newton(3, fun, jac, ti+k*dt, dt, sol(k,:), sol(k-2:k,:));
                t(k+1) = ti + k*dt;
                k = k + 1;
            end
        end
        
        function y = newton(obj, p, fun, jac, t, dt, yi, ypre)
            tol = 1e-14;
            maxiter = 100;
            %{
            Newton's method for nonlinear root-finding.
            p - the order of method to use.
            fun - the function whose root to find, with signature fun(t,y).
            jac - the Jacobian of fun, with signature jac(t,y).
            t - the integration time to solve for.
            dt - the integration step size.
            yi - initial guess for solution vector.
            ypre - the previous solutions needed for the multistep method. 
            tol - stopping tolerance for residual.
            maxiter - maximum number of iterations allowed for convergence.
            %}
            
            % Define some shorthands for class variables:
            m = obj.m; % number of differential variables
            n = obj.n; % number of algebraic variables
            % BDF coefficients for order p
            alpha = obj.a{p};
            beta = obj.b(p);
            
            % Your code here %
            
        end
    end
end
