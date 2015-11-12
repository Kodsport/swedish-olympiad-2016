// forvirradforelasare
// Arash Rouahani

object Arash {
  def main(args: Array[String]) {
    val numWeeks = readLine.toInt
    val classesPerWeek: List[Int] = readLine.split(" ").map(_.toInt).toList
    val zippedList: List[(Int, Int)] = classesPerWeek zip (classesPerWeek.tail)
    val diffList = zippedList.map(p => p._2-p._1)
    val positives = diffList.filter { _ > 0 }
    val negatives = diffList.filter { _ < 0 }
    println("%s %s".format(-(negatives.sum), positives.sum))
  }
}
