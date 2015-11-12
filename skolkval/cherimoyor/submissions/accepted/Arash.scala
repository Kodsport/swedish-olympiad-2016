// Arash Rouhani
// 12-nov-2015
// HCMC

object Cherimoyor {
  def main(args: Array[String]) {

     def points_for_using(num_cherimoya: Int) :Int = {
       if(num_cherimoya > 10)
         55
       else
         55 - (10-num_cherimoya)*(10-(num_cherimoya-1))/2
     }
     assume(points_for_using(0) == 0)
     assume(points_for_using(1) == 10)
     assume(points_for_using(2) == 19)
     assume(points_for_using(9) == 54)
     assume(points_for_using(10) == 55)
     assume(points_for_using(25) == 55)

     val cherimoyor: Array[Int] = readLine.split(" ").map(_.toInt)
     val mem = Array.fill(11, 300)(-10000)  // [day, num_used], where "num_used" == num_eaten+num_thrown

     def min_used(day: Int) :Int = {
       cherimoyor.slice(0, Math.max(0, day-2)).sum
     }

     def max_used(day: Int) :Int = {
       cherimoyor.slice(0, Math.min(7,day)).sum
     }

     mem(0)(0) = 0
     for(i <- 0 to 9; j <- 0 to 299; use <- 0 to 30) {
       val candidate_value = mem(i)(j) + points_for_using(use)
       val is_valid = min_used(i+1) <= j+use && j+use <= max_used(i+1);
       if(is_valid) {
         mem(i+1)(j+use) = Math.max(mem(i+1)(j+use), candidate_value)
       }
     }
     println(mem.flatten.max)
  }
}
