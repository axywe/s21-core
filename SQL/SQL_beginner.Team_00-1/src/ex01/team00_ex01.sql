with t as (
        with recursive _n as
        (select point1,
                point2,
                cost,
                1 as level,
                array[point1] AS path,
                FALSE AS cycle,
                array[cost] AS costs
        from nodes
        where point1 = 'a'
        union all
        select nodes.point1,
                nodes.point2,
                nodes.cost+_n.cost as cost,
                _n.level+1 as level,
                _n.path || nodes.point1 AS path,
                nodes.point1 = ANY (_n.path) AS cycle,
                _n.costs || nodes.cost AS costs
        from nodes inner join _n on _n.point2 = nodes.point1 and not cycle
        )
        select
            cost - costs[5] as total_cost,
            path as tour
        from _n
        where level =5 and
            'a' = ANY(path) and
            'b' = ANY(path) and
            'c' = ANY(path) and
            'd' = ANY(path)
           and path[1] = path[5]
        order by cost, path)
        select distinct *
        from t
        where total_cost = (select  min(total_cost) from t) or
            total_cost = (select  max(total_cost) from t)
        order by 1,2;
